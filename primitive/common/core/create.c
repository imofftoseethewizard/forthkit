pr_create:
{
    /* CREATE ( -- )

       A defining word executed in the form:

       |   CREATE <name>

       Creates a dictionary entry for <name>.  After <name> is
       created, the next available dictionary location is the first
       byte of <name>'s parameter field.  When <name> is
       subsequently executed, the address of the first byte of
       <name>'s parameter field is left on the stack.  CREATE does
       not allocate space in <name>'s parameter field.
     */

    _store_word_name();

    /* Indicates that this word can be inlined during compilation. */
    _word_header(c_inline2);

    /* Compile the word. It just puts a literal on the stack. */
    _compile_pr(op_literal);

    /* dp + 2 is the location immediately after the exit below. */
    _store_data(_from_ptr((cell *)dp + 2));
    _compile_pr(op_exit);

    _end_define_word();

    _check_dictionary_bounds();
}
