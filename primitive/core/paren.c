_primitive(pr_paren) {
    /* Skip leading delimiters. */
    while (source_idx < source_len && source[source_idx] != ')')
        source_idx++;

    e[ea_source_idx] = source_idx;

    if (source_idx == source_len)
        _abort();

    _next();
}

_define_primitive("(", pr_paren);
