primitive pr_abort_quote()
{
    /* ABORT" ( flag -- )
              compiling: ( -- )

       Used in the form:

       |   flag ABORT" ccc"

       When later executed, if flag is true the characters ccc,
       delimited by " (close-quote), are displayed and then a
       system dependent error abort sequence, including the
       function of ABORT , is performed.  If flag is false, the
       flag is dropped and execution continues.  The blank
       following ABORT" is not part of ccc.

     */

    _compile_if();

    register char *source      = (char *)_to_ptr(e[ea_source_addr]);
    register cell source_len   = e[ea_source_len];
    register cell source_idx   = e[ea_source_idx] + 1; /* skip space after ." */

    register cell *jump_offset = (cell *)dp + 1;
    register char *s, *s0 = dp + 2*sizeof(cell);

    _compile_pr(op_jump);
    _store_data(0);

    s = s0;
    while (source_idx < source_len && source[source_idx] != '"')
        *s++ = source[source_idx++];

    e[ea_error_msg_addr] = _from_ptr(s0);
    e[ea_error_msg_len] = s - s0;

    *s++ = 0; /* a convenience for usage by c */

    dp = (char *)_align(s);

    *jump_offset = (cell)(dp - (char *)jump_offset);

    _compile_pr(op_literal);
    _store_data(err_abort_message);
    _compile_pr(op_abort);

    _compile_then();

    _check_dictionary_bounds();

    if (source_idx == source_len)
        _abort(err_unexpected_end_of_file);

    e[ea_source_idx] = source_idx + 1; /* skip final quote */
}
