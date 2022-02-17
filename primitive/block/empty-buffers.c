_primitive(pr_empty_buffers) {
    for (register int i = 0; i < BUFFER_COUNT; i++)
        e[e[ea_buffers] + i] = -1;
    _next();
}
_define_primitive("EMPTY-BUFFERS", pr_empty_buffers);
