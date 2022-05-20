__primitive(pr_update)
{
    register cell i = (e[ea_next_buffer] + e[ea_buffer_count] - 1) % e[ea_buffer_count];
    *(_to_ptr(e[ea_buffers]) + i) |= c_msb;
}
__end
__define_primitive("UPDATE", pr_update);
