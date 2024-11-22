/*|

`REPEAT` compiling: `( sys -- )`

Used in the form:

    BEGIN ... flag WHILE ... REPEAT

At execution time, `REPEAT` continues execution to just after the
corresponding `BEGIN`. sys is balanced with its corresponding `WHILE`.

  |*/

// REPEAT immediate

pr_repeat:
{
    _compile_repeat();
    _check_dictionary_bounds();
}
