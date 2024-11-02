pr_empty_buffers:
{
    for (register int i = 0; i < e[ea_buffer_count]; i++)
        *(_to_ptr(e[ea_buffer_map]) + i) = -1;
}
