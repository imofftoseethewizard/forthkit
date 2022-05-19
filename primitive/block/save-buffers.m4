__primitive(pr_save_buffers)
{
    register cell n;
    register cell block;

    for (n = 0; n < BUFFER_COUNT; n++) {

        block = e[e[ea_buffers] + n];

        /* empty */
        if (block == -1)
            continue;

        /* dirty bit */
        if (!(block & c_msb))
            continue;

        if (   storage_fd < 0
               || lseek(storage_fd, (block ^ c_msb)*e[ea_buffer_size], SEEK_SET) == -1
               || write(storage_fd, _buffer_addr(n), e[ea_buffer_size]) == -1
            ) {

            _abort(-34);
            break;
        }
    }
}
__end
__define_primitive("SAVE-BUFFERS", pr_save_buffers);
