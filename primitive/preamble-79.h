#define c_immediate 0b0001
#define c_inline    0b0010
#define c_primitive 0b0100
#define c_value     0b1000

#define _quote(x) #x
#define _register_operator(x, y)                                           \
    do {                                                                   \
        if (!e[ea_context]) {                                              \
            _debug("operator %-16s %lx\n", _quote(y), (long)_pr_addr(y));  \
            operators[x] = _pr_addr(y);                                    \
        }                                                                  \
    } while (0)

#define _string_len(x)  *(length_type *)(x)
#define _string_addr(x) (char *)((length_type *)(x) + 1)

     /* Note that this assumes that a cell is an power of 2 number of bytes.
        That seems like a safe assumption.
     */

#define _align(x) (cell *)((long)(x) + sizeof(cell) - 1 & ~(sizeof(cell) - 1))

#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#define _store_data(x)                                                     \
     here = (char *)_align(here), *(cell *)here = (cell)(x), here += sizeof(cell)

#define _compile_pr(x) _store_data(_pr_addr(x))

#define _set_word_flags(x, flags)               *((cell *)(x) + 2) |= (flags)
#define _clear_word_flags(x, flags)             *((cell *)(x) + 2) &= ~(flags)
#define _get_word_flags(x, flags)               *((cell *)(x) + 2) & ~(flags)

#define _get_word_interpretation_ptr(x) ((cell *)(x) + 3)
#define _get_word_interpretation(x)     _from_ptr(_get_word_interpretation_ptr(x))

#define _store_word_name()                                                 \
do {                                                                       \
    register cell name = _from_ptr(here);                                  \
    register cell *string_addr = _to_ptr(*sp);                             \
    register length_type n = *(length_type *)string_addr;                  \
                                                                           \
    memcpy(here, string_addr, n + sizeof(length_type));                    \
    here += n + sizeof(length_type);                                       \
                                                                           \
    *sp = name;                                                            \
                                                                           \
} while (0)


#define _word_header(flags)                                                \
       /* _word_header: ( n -- addr ) [xp]    */                           \
                                                                           \
       /* Align here to a cell boundary.      */                           \
       here = (char *)_align(here);                                        \
                                                                           \
       /* Save address of new word.           */                           \
       *--rp = _from_ptr(here);                                            \
                                                                           \
       /* Copy name address to word entry.    */                           \
       _store_data(*sp++);                                                 \
                                                                           \
       /* Vocabulary list link.               */                           \
       _store_data(e[e[ea_current]]);                                      \
                                                                           \
       /* Add to current vocabulary.          */                           \
       e[e[ea_current]] = *rp++;                                           \
                                                                           \
       /* Word flags.                         */                           \
       _store_data(flags)

#define _next_word(x) *(_to_ptr(x) + 1)

#define _begin_define_word(s, flags)                                       \
    do {                                                                   \
        *--sp = _from_ptr(here);                                           \
        here = store_counted_string((s), here);                            \
        _word_header(flags);                                               \
    } while(0)

#define _define_primitive_ext(s, l, flags)                                 \
    if (!e[ea_context])                                                    \
    {                                                                      \
        _info("defining %-16s %lx\n", s, (long)_pr_addr(l));               \
        _begin_define_word(s, c_inline | c_primitive | (flags));           \
        _compile_pr(l);                                                    \
        _compile_pr(op_exit);                                              \
    }

#define _define_parsing_primitive(s, l)                                    \
    if (!e[ea_context])                                                    \
    {                                                                      \
        _info("defining %-16s %lx\n", s, (long)_pr_addr(l));               \
        _begin_define_word(s, c_primitive);                                \
        _compile_pr(op_literal);                                           \
        _store_data(32);                                                   \
        _compile_pr(pr_word);                                              \
        _compile_pr(l);                                                    \
        _compile_pr(op_exit);                                              \
    }

#define _define_primitive(s, l)           _define_primitive_ext(s, l, 0)
#define _define_immediate_primitive(s, l) _define_primitive_ext(s, l, c_immediate)

#define _compiled_word(s, flags)                                           \
    if (!e[ea_context]) _begin_define_word(s, flags);                      \
    if (!e[ea_context])