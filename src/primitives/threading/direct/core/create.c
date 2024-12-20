/*|

`CREATE ( -- )`

A defining word executed in the form:

    CREATE <name>

Creates a dictionary entry for `<name>`.  After `<name>` is created,
the next available dictionary location is the first byte of `<name>`'s
parameter field.  When `<name>` is subsequently executed, the address
of the first byte of `<name>`'s parameter field is left on the stack.
`CREATE` does not allocate space in `<name>`'s parameter field.

Note that this primitive is not exposed as `CREATE` in the dictionary.
There is a compiled word which first calls `32 WORD` and then this
primitive.

  |*/


pr_create:
{
    _store_word_name();
    _word_header(0);

    // TODO threading

    /* Compile the word. It just puts a literal on the stack. */
    _compile_pw(op_literal);

    /* dp + 2 is the location immediately after the exit below. */
    _store_data(_from_ptr((cell *)dp + 2));
    _compile_pw(op_exit);

    _end_define_word();

    _check_dictionary_bounds();
}
