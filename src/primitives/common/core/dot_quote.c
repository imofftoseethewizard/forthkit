/*|

`." ( -- )`

Used in the form:

    ." ccc"

Later execution will display the characters `ccc` up to but not
including the delimiting `"` (close-quote).  The blank following `."`
is not part of `ccc`.

The standards do not define interpretation semantics for this word.  In
this implementation, the characters are provided to `EMIT` as they are
read from the current input.

  |*/

// ." immediate

pr_dot_quote:
{
    register char *source      = (char *)_to_ptr(e[ea_source_addr]);
    register cell source_len   = e[ea_source_len];
    register cell source_idx   = e[ea_source_idx] + 1; /* skip space after ." */

    if (_state()) {

        register cell *jump_offset = (cell *)dp + 3;
        register char *s, *s0 = dp + 4*sizeof(cell);

        _compile_pw(op_literal);
        _store_data(_from_ptr(s0));

        _compile_pw(op_jump);
        _store_data(0);

        s = s0;
        while (source_idx < source_len && source[source_idx] != '"')
            *s++ = source[source_idx++];

        *jump_offset = (cell)((char *)_align(s) - (char *)jump_offset);

        dp = (char *)_align(s);

        _compile_pw(op_literal);
        _store_data(s - s0);
        _compile_pw(pr_type);

        _check_dictionary_bounds();

    } else {
        while (source_idx < source_len && source[source_idx] != '"') {
            *--sp = source[source_idx++];
            _emit();
        }
    }

    if (source_idx == source_len)
        _abort(err_unexpected_end_of_file);

    e[ea_source_idx] = source_idx + 1; /* skip final quote */

}
