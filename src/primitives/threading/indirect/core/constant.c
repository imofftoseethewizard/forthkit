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
    _word_header(0);

    /* adds the word to the current vocabulary */
    _end_define_word();

    /* Compile the word. It just puts a literal on the stack. */

    _compile_pr(op_do_const);
    _store_data(*sp++);

    _check_dictionary_bounds();
}
