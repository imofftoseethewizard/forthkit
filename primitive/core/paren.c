_primitive(pr_paren) {
    register cell source_len   = e[ea_source_len];
    register cell source_idx   = e[ea_source_idx];

    while (source_idx < source_len && source[source_idx] != ')')
        source_idx++;

    e[ea_source_idx] = source_idx;

    if (source_idx == source_len)
        _abort();

    _next();
}

_define_primitive("(", pr_paren);
