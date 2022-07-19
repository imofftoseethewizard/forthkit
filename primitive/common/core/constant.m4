__primitive(pr_constant)
{
    /* CONSTANT ( n -- )

       A defining word used in the form:

       |   n CONSTANT <name>

       to create a dictionary entry for <name>, leaving n in its
       parameter field. When <name> is later executed, n will be
       left on the stack.
     */

    _store_word_name();

    /* Indicates that this word can be inlined as 2 cells during compilation. */
    _word_header(c_value);

    /* adds the word to the current vocabulary */
    _end_define_word();

    /* Compile the word. It just puts a literal on the stack. */
    _compile_pr(op_literal);
    _store_data(*sp++);
    _compile_pr(op_exit);

    _check_dictionary_bounds();
}
__end
__define_parsing_primitive("CONSTANT", pr_constant);
