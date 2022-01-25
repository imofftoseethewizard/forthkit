define_parsing_primitive("FIND", &&p1_do_find);

#define _string_len(x)  *(length_type *)(x)
#define _string_addr(x) (char *)((length_type *)(x) + 1)

#define _lowercase_ascii(x) ((x) < 'A' || (x) > 'Z' ? (x) : (x) - 'A' + 'a')

/* Some aliases for readablilty. */
#define name           *sp
#define name_cp        cp0
#define name_len       l0
#define word           xp
#define word_name      yp
#define word_name_cp   cp1

if (0) {
  p1_do_find:

    /* Save the length of the target string into k. */
    name_len = _string_len(name);

    /* word will hold the address of the word being checked for a matching
       name.
    */
    word = context;

    while (word) {

        word_name = *word;

        if (_string_len(word_name) == name_len) {

            name_cp = _string_addr(name);
            word_name_cp = _string_addr(word_name);

            for (i = 0; i < name_len; i++, name_cp++, word_name_cp++)
                if (_lowercase_ascii(*name_cp) != _lowercase_ascii(*word_name_cp))
                    break;

            if (i == name_len)
                break;

            word = _next_word(word);
        }
    }

    if (!word) {
        *--sp = word;
        /* name is now invalid */
        /* stack contains ( name 0 ) */
    } else {
        sp++;
        /* name is now invalid */
        *--sp = _get_word_cfa(word);
        *--sp = _get_word_flags(word, c_immediate) ? 1 : -1;
        /* stack contains ( xt 1 ) or ( xt -1 ) */
    }

    _next();
}

#undef name
#undef name_cp
#undef name_len
#undef word
#undef word_name
#undef word_name_cp
