_primitive(pr_update) {
    register cell i = (e[ea_next_buffer] + BUFFER_COUNT - 1) % BUFFER_COUNT;
    e[ea_buffers + i] |= c_msb;
    _next();
}

_define_primitive("UPDATE", pr_update);
