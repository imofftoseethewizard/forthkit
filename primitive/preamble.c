#define c_immediate 0b0001
#define c_inline    0b0010
#define c_primitive 0b0100

#define _string_len(x)  *(length_type *)(x)
#define _string_addr(x) (char *)((length_type *)(x) + 1)

     /* Note that this assumes that a cell is an power of 2 number of bytes.
        That seems like a safe assumption.
     */

#define _align(x) (cell *)((cell)(x) + sizeof(cell) - 1 & ~(sizeof(cell) - 1))

#define _store_data(x)                           \
     here = (char *)_align(here), *(cell *)here = (cell)(x), here += sizeof(cell)

#define _word_header(flags)                      \
       /* _word_header: ( n -- addr ) [xp]    */ \
                                                 \
       /* Align here to a cell boundary.      */ \
       here = (char *)_align(here);              \
                                                 \
       /* Save address of new word.           */ \
       *--rp = (cell *)here;                     \
                                                 \
       /* Copy name address to word entry.    */ \
       _store_data(*sp++);                       \
                                                 \
       /* Vocabulary list link.               */ \
       _store_data(current);                     \
                                                 \
       /* Add to current vocabulary.          */ \
       current = *rp;                            \
                                                 \
       /* Word flags.                         */ \
       _store_data(flags);                       \
                                                 \
       /* Compilation semantics               */ \
       _store_data(&&pr_store_compiled);      /*    \ */
       /*                                           \ */
       /* /\* Return the address of the new word. *\/ \ */
       /* *--sp = (cell)*rp++ */

#define _next_word(x) (cell *)*((cell *)(x) + 1)

#define begin_define_word(s, flags)                    \
    *--sp = (cell)here;\
    here = store_counted_string((s), here);                   \
    _word_header(flags);

#define define_primitive_ext(s, l, flags)              \
    if (!context)                                      \
    {                                                  \
        _debug("defining %-16s (%lx)\n", s, (cell)l);  \
        begin_define_word(s, c_primitive | (flags));   \
        _store_data(l);                                \
        _store_data(&&op_exit);                        \
    }

#define define_parsing_primitive(s, l)                 \
    if (!context)                                      \
    {                                                  \
        begin_define_word(s, c_primitive);             \
        _store_data(&&pr_word);                        \
        _store_data(l);                                \
        _store_data(&&op_exit);                        \
    }

#define define_primitive(s, l)           define_primitive_ext(s, l, 0)
#define define_immediate_primitive(s, l) define_primitive_ext(s, l, c_immediate)

#define _set_word_flags(x, flags)               *((cell *)(x) + 2) |= (flags)
#define _clear_word_flags(x, flags)             *((cell *)(x) + 2) &= ~(flags)
#define _get_word_flags(x, flags)               *((cell *)(x) + 2) & ~(flags)

#define _get_word_compilation_semantics(x)      *((cell *)(x) + 3)
#define _get_word_interpretation_semantics(x)   ((cell *)(x) + 4)
