pr_dot_paren:
{
    register char *source      = (char *)_to_ptr(e[ea_source_addr]);
    register cell source_len   = e[ea_source_len];
    register cell source_idx   = e[ea_source_idx] + 1; /* skip space after ." */

    while (source_idx < source_len && source[source_idx] != ')') {
        *--sp = source[source_idx++];
        _emit();
    }

    if (source_idx == source_len)
