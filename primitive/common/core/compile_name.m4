__primitive(pr_compile_name)
{
    register byte
      *lenp = dp++,
      *source = (byte *)_to_ptr(e[ea_source_addr]);

    register cell
      len = e[ea_source_len],
      idx = e[ea_source_idx];

    register byte w_len = 0;

    while (source[idx] == 32 && idx < len)
        idx++;

    while (source[idx] != 32 && idx < len && w_len < (byte)-1)
        *dp++ = source[idx++];

    *lenp = (byte *)dp - lenp - 1;
    *--sp = _from_ptr(lenp);

    e[ea_source_idx] = idx;
}
__end
__define_primitive("name:", pr_compile_name);
