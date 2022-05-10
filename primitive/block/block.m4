__primitive(pr_read_block)  
{

    register char *buffer = (char *)_to_ptr(*sp++);
    register cell n = *sp++;

    if (   storage_fd < 0
        || lseek(storage_fd, n*BUFFER_SIZE, SEEK_SET) == -1
        || read(storage_fd, buffer, BUFFER_SIZE) == -1
        )

        _abort(-33);

    else
        *--sp = _from_ptr(buffer);

}
__end
