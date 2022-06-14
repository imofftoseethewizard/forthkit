__primitive(pr_read_block)
{
    /* BLOCK ( u -- addr )

       addr is the address of the assigned buffer of the first byte
       of block u.  If the block occupying that buffer is not block
       u and has been UPDATEed it is transferred to mass storage
       before assigning the buffer.  If block u is not already in
       memory, it is transferred from mass storage into an assigned
       block buffer.  A block may not be assigned to more than one
       buffer.  If u is not an available block number, an error
       condition exists.  Only data within the last buffer
       referenced by BLOCK or BUFFER is valid.  The contents of a
       block buffer must not be changed unless the change may be
       transferred to mass storage.
     */

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
__end
__define_primitive("<read-block>", pr_read_block);
