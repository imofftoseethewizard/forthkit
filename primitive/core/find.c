define_parsing_primitive("FIND", &&pr_find);

#define _lowercase_ascii(x) ((x) < 'A' || (x) > 'Z' ? (x) : (x) - 'A' + 'a')

if (0) {

    register cell *name, *word, *word_name;
    register char *name_cp, *word_name_cp;
    register int i, name_len;

  pr_find:
    name = (cell *)*sp;

    /* Save the length of the target string into k. */
    name_len = _string_len(name);

    _debug("name: %.*s\n", _string_len(name), _string_addr(name));
    /* word will hold the address of the word being checked for a matching
       name.
    */
    word = context;

    while (word) {

        word_name = (cell *)*word;

        if (_string_len(word_name) == name_len) {

            name_cp = _string_addr(name);
            word_name_cp = _string_addr(word_name);

            for (i = 0; i < name_len; i++, name_cp++, word_name_cp++)
                if (_lowercase_ascii(*name_cp) != _lowercase_ascii(*word_name_cp))
                    break;

            if (i == name_len)
                break;

        }
        word = _next_word(word);
    }

    if (!word) {
        *--sp = 0;
        /* stack contains ( name 0 ) */
    } else {
        *sp = (cell)_get_word_interpretation_semantics(word);
        *--sp = _get_word_flags(word, c_immediate) ? 1 : -1;
        /* stack contains ( xt 1 ) or ( xt -1 ) */
    }

    _next();
}
