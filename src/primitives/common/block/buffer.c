/*|

`BUFFER ( u -- addr )`

Assigns a block buffer to block u.  addr is the address of the first
byte of the block within its buffer.  This function is fully specified
by the definition for BLOCK except that if the block is not already in
memory it might not be transferred from mass storage.  The contents of
the block buffer assigned to block u by BUFFER are unspecified.

  |*/

// BUFFER

pr_buffer:
{
    register cell new_block = *sp++;
    register cell n = e[ea_next_buffer];
    register cell old_block = *(_to_ptr(e[ea_buffer_map]) + n);

    if (old_block != (cell)-1 && old_block & c_msb) {

        if (   storage_fd < 0
               || lseek(storage_fd, (old_block ^ c_msb)*e[ea_buffer_size], SEEK_SET) == -1
               || write(storage_fd, _to_buffer_ptr(n), e[ea_buffer_size]) == -1
            ) {

            _abort(err_block_write_exception);
            goto pr_buffer_exit;
        }
    }

    *(_to_ptr(e[ea_buffer_map]) + n) = new_block;
    *--sp = _from_ptr(_to_buffer_ptr(n));
    e[ea_next_buffer] = (n + 1) % e[ea_buffer_count];

  pr_buffer_exit:
    ;
}
