#define c_immediate 0b0001
#define c_inline    0b0010
#define c_primitive 0b0100

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
       xp = (cell *)here;                        \
                                                 \
       /* Copy name address to word entry.    */ \
       _store_data(*sp++);                       \
                                                 \
       /* Vocabulary list link.               */ \
       _store_data(current);                     \
                                                 \
       /* Add to current vocabulary.          */ \
       current = xp;                             \
                                                 \
       /* Word flags.                         */ \
       _store_data(flags);                       \
                                                 \
       /* Return the address of the new word. */ \
       *--sp = (cell)xp

#define _next_word(x) (cell *)*((cell *)(x) + 1)

#define begin_define_word(s)                     \
     *--sp = (cell)here;                         \
     here = store_cstring((s), here);            \

#define define_primitive_ext(s, l, flags)        \
     if (!context)                               \
     {                                           \
          begin_define_word(s);                  \
          _word_header(c_primitive | (flags));   \
          _store_data(l);                        \
          _store_data(&&op_exit);                \
     }

#define define_parsing_primitive(s, l)           \
     if (!context)                               \
     {                                           \
          begin_define_word(s);                  \
          _word_header(c_primitive);             \
          _store_data(&&pr_word);                \
          _store_data(l);                        \
          _store_data(&&op_exit);                \
     }

#define define_primitive(s, l)           define_primitive_ext(s, l, 0)
#define define_immediate_primitive(s, l) define_primitive_ext(s, l, c_immediate)

#define _set_word_flags(x, flags)   *((cell *)(x) + 2) |= (flags)
#define _clear_word_flags(x, flags) *((cell *)(x) + 2) &= ~(flags)
#define _get_word_flags(x, flags)   *((cell *)(x) + 2) & ~(flags)
#define _get_word_cfa(x)            *((cell *)(x) + 3)
