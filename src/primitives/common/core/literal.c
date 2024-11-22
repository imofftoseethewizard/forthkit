/*|

`LITERAL` compiling: `( n -- )` run-time `( -- n )`

If compiling, then compile the stack value n as a single cell literal,
which when later executed, will leave n on the stack.

  |*/

// LITERAL immediate

pr_literal:
{
	// TODO threading
    _compile_pr(op_literal);
    _store_data(*sp++);
    _check_dictionary_bounds();
}
