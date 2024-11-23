/*|

`CONSTANT ( n -- )`

A defining word used in the form:

    n CONSTANT <name>

to create a dictionary entry for `<name>`, leaving `n` in its
parameter field. When `<name>` is later executed, `n` will be left on
the stack.

  |*/

// CONSTANT

pr_constant:
{
    _store_word_name();

    /* Indicates that this word can be inlined as 2 cells during compilation. */
    _word_header(c_inline2);

    /* adds the word to the current vocabulary */
    _end_define_word();

    /* Compile the word. It just puts a literal on the stack. */
    // TODO threading: replace op_literal with do_literal
    _compile_pw(op_literal);
    _store_data(*sp++);
    _compile_pw(op_exit);

    _check_dictionary_bounds();
}