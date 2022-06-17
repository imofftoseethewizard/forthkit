__primitive(pr_paren)
{
    /* ( ( -- ) "paren"

       Used in the form:

       |   ( ccc)

       The characters ccc, delimited by ) (closing parenthesis),
       are considered comments.  Comments are not otherwise
       processed.  The blank following ( is not part of ccc.  ( may
       be freely used while interpreting or compiling.  The number
       of characters in ccc may be zero to the number of characters
       remaining in the input stream up to the closing parenthesis.

       An error condition exists if the input stream is exhausted
       before the right parenthesis.
     */

    register char *source      = (char *)_to_ptr(e[ea_source_addr]);
    register cell source_len   = e[ea_source_len];
    register cell source_idx   = e[ea_source_idx];

    while (source_idx < source_len && source[source_idx] != ')')
        source_idx++;

    if (source_idx < source_len)
        /* skip paren */
        e[ea_source_idx] = source_idx+1;
    else {
        e[ea_source_idx] = source_idx;
        _abort(err_unexpected_end_of_file);
    }
}
__end
__define_immediate_primitive(``"("'', pr_paren);
