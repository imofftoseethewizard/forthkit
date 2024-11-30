/*|

`CREATE ( -- )`

A defining word executed in the form:

    CREATE <name>

Creates a dictionary entry for `<name>`.  After `<name>` is created,
the next available dictionary location is the first byte of `<name>`'s
parameter field.  When `<name>` is subsequently executed, the address
of the first byte of `<name>`'s parameter field is left on the stack.
`CREATE` does not allocate space in `<name>`'s parameter field.

The implementation below implements the newly created word as a
constant, returning the address of the next cell after the value
stored, for example in a 4-byte cell implementation we might have

    1000: op_do_const
    1004: 1008
    1008: ...

This is functionally equivalent to

    1000: op_do_var
    1004: ...

in the sense that both will return the address of the cell marked with
the ellipsis.  The latter, however, would not admit the rewriting
required to implement `DOES>`, which will replace the `pr_do_const`
and its value with `pr_do_does` and the offset to the does code.

  |*/

pr_create:
{
    _store_word_name();
    _word_header(0);

    _compile_pr(op_do_const);
    _store_data(_from_ptr((cell *)dp + 1));

    _end_define_word();

    _check_dictionary_bounds();
}
