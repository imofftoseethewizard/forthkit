/*|

`; ( -- ) compiling: ( sys -- )`

Stops compilation of a colon definition, allows the `<name>` of this
colon definition to be found in the dictionary, sets interpret state
and compiles `EXIT` (or a system dependent word which performs an
equivalent function).  `sys` is balanced with its corresponding `:`.

  |*/

// ; immediate

pr_semicolon:
{
    _compile_pw(op_exit);
    _set_state(0);

    _check_dictionary_bounds();
}
