__primitive(pr_update)  
{
    register cell i = (e[ea_next_buffer] + BUFFER_COUNT - 1) % BUFFER_COUNT;
    e[ea_buffers + i] |= c_msb;
}
__end
__define_primitive("UPDATE", pr_update);
