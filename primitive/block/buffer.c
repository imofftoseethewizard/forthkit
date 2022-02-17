_primitive(pr_buffer) {
    *--sp = _from_ptr((char *)e + e[ea_size] - BUFFER_SIZE * (e[ea_next_buffer] + 1));
    e[ea_next_buffer] = (e[ea_next_buffer] + 1) % BUFFER_COUNT;
    _next();
}

_define_primitive("BUFFER", pr_buffer);
