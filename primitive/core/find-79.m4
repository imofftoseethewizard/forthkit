#define _lowercase_ascii(x) ((x) < 'A' || (x) > 'Z' ? (x) : (x) - 'A' + 'a')

__primitive(pr_find)
{
    /* FIND ( -- addr )

       Leave the compilation address of the next word name, which is
       accepted from the input stream. If that word cannot be found
       in the dictionary after a search of CONTEXT and FORTH leave
       zero.
    */

    register cell *name, word, *wordp, *word_name_cs;
    register char *name_cp, *word_name_cp;
    register int i, name_len;

    name = _to_ptr(*sp);

    /* Save the length of the target string into k. */
    name_len = _string_len(name);

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

    if (!word)
        *sp = 0;
    else
        *sp = _get_word_interpretation(wordp);

}
__end
__define_primitive("<find>", pr_find);
