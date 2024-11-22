/*|

`FIND ( addr1 -- addr1 n | addr2 n )`

`addr1` is the address of a counted string.  The string contains a
word name to be located in the currently active search order.  If the
word is not found, `addr2` is the string address `addr1`, and n is
zero.  If the word is found, `addr2` is the compilation address and
`n` is set to one of two non-zero values.  If the word found has the
immediate attribute, `n` is set to one.  If the word is non-immediate,
`n` is set to minus one (true).

  |*/

// FIND

pr_find:
{
    register cell *name, word, *wordp, *word_name_cs;
    register char *name_cp, *word_name_cp;
    register int i, name_len;

    name = _to_ptr(*sp);

    /* Save the length of the target string into k. */
    name_len = _string_len(name);

    // TODO concurrency

    /* word will hold the address of the word being checked for a matching
       name.
    */
    word = *_to_ptr(tp[ta_context]);

    while (word) {
        wordp = _to_ptr(word);
        word_name_cs = _to_ptr(*wordp);

        if (_string_len(word_name_cs) == name_len) {

            name_cp = _string_addr(name);
            word_name_cp = _string_addr(word_name_cs);

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
        *sp = (cell)_get_word_interpretation(wordp);
        *--sp = _get_word_flags(wordp) & c_immediate ? 1 : -1;
        /* stack contains ( xt 1 ) or ( xt -1 ) */
    }
}
