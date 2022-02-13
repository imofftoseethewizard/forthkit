_primitive(pr_dot_quote) {

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

    if (source_idx == source_len)
        _abort();

    e[ea_source_idx] = source_idx + 1; /* skip final quote */

    _next();
}

_define_immediate_primitive(".\"", pr_dot_quote);
