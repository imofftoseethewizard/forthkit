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

    __compiled_word("BLOCK", cw_block, 0)
    _compile_pr(pr_dup);
    _compile_pr(pr_buffer);
    _compile_pr(pr_read_block);
    _compile_pr(op_exit);
