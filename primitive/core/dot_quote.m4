__primitive(pr_dot_quote)  
{

    register char *source      = (char *)_to_ptr(e[ea_source_addr]);
    register cell source_len   = e[ea_source_len];
    register cell source_idx   = e[ea_source_idx] + 1; /* skip space after ." */

    if (e[ea_state]) {

        register cell *jump_offset = (cell *)here + 3;
        register char *s, *s0 = here + 4*sizeof(cell);

        _compile_pr(op_literal);
        _store_data(_from_ptr(s0));

        _compile_pr(op_jump);
        _store_data(0);

        s = s0;
        while (source_idx < source_len && source[source_idx] != '"')
            *s++ = source[source_idx++];

        *jump_offset = (cell)((char *)_align(s) + sizeof(cell) - (char *)jump_offset);

        here = (char *)_align(s);

        _compile_pr(op_literal);
        _store_data(s - s0);
        _compile_pr(pr_type);

     } else {

        while (source_idx < source_len && source[source_idx] != '"') {
            *--sp = source[source_idx++];
            _emit();
        }

    }

    if (source_idx == source_len) {
        /* see https://forth-standard.org/standard/exception */
        *--sp = -39; /* unexpected end of file */
        _abort();
    }

    e[ea_source_idx] = source_idx + 1; /* skip final quote */

}
__end
__define_immediate_primitive(".\"", pr_dot_quote);
