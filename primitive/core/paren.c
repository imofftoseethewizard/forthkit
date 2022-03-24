_primitive(pr_paren) {
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
        *--sp = -39;
        _abort();
    }


    _next();
}
