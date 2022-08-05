__primitive(pr_save_buffers)
{
    /* SAVE-BUFFERS ( -- )

       The contents of all block buffers marked as UPDATEd are
       written to their corresponding mass storage blocks.  All
       buffers are marked as no longer being modified, but may
       remain assigned. An error condition results if mass-
       storage writing is not completed.
     */

    register cell n;
    register cell block;

    for (n = 0; n < e[ea_buffer_count]; n++) {

        block = *(_to_ptr(e[ea_buffer_map]) + n);

        /* empty */
        if (block == -1)
            continue;

        /* dirty bit */
        if (!(block & c_msb))
            continue;

        if (   storage_fd < 0
               || lseek(storage_fd, (block ^ c_msb)*e[ea_buffer_size], SEEK_SET) == -1
               || write(storage_fd, _to_buffer_ptr(n), e[ea_buffer_size]) == -1
            ) {

            _abort(err_block_write_exception);
            break;
        }

        /* clear dirty bit */
        *(_to_ptr(e[ea_buffer_map]) + n) = block & ~c_msb;
    }
}
__end
__define_primitive("save-buffers", pr_save_buffers);
