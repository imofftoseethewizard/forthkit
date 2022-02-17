_primitive(pr_update) {
    register cell i = (e[ea_next_buffer] + BUFFER_COUNT - 1) % BUFFER_COUNT;
    e[ea_buffers + i] |= 1 << (sizeof(cell) * 8 - 1);
    _next();
}

_define_primitive("UPDATE", pr_update);
