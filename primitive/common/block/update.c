primitive pr_update()
{
    /* UPDATE ( -- )

       Mark the most recently referenced block as modified. The
       block will subsequently be automatically transferred to mass
       storage should its memory buffer be needed for storage of a
       different block, or upon execution of SAVE-BUFFERS.
     */

    register cell i = (e[ea_next_buffer] + e[ea_buffer_count] - 1) % e[ea_buffer_count];
    *(_to_ptr(e[ea_buffer_map]) + i) |= c_msb;
}
