pr_2constant:
{
    /* 2CONSTANT ( x1 x2 -- )

       A defining word used in the form:

       |   x1 x2 2CONSTANT <name>

       to create a dictionary entry for <name>, leaving x1 in its
       parameter field. When <name> is later executed, n will be
       left on the stack.
     */

    _store_word_name();

    /* inline this word when compiling, 3 cells long */
    _word_header(c_inline3);

    /* adds the word to the current vocabulary */
    _end_define_word();

    /* Compile the word. It just puts a literal on the stack. */
    _compile_pr(op_2literal);
    _store_data(*(sp+1));
    _store_data(*sp);

    sp += 2;

    _compile_pr(op_exit);

    _check_dictionary_bounds();
}
