primitive pr_read_block()
{
    register char *buffer = (char *)_to_ptr(*sp++);
    register cell n = *sp++;

    if (   storage_fd < 0
        || lseek(storage_fd, n*e[ea_buffer_size], SEEK_SET) == -1
        || read(storage_fd, buffer, e[ea_buffer_size]) == -1
        )

        _abort(err_block_read_exception);

    else
        *--sp = _from_ptr(buffer);
}
