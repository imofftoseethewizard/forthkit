#define _buffer_addr(n) (char *)e + e[ea_size] - BUFFER_SIZE * ((n) + 1)

__primitive(pr_buffer)  
{
    register cell new_block = *sp++;
    register cell n = e[ea_next_buffer];
    register cell old_block = e[ea_buffers + n];

    if (old_block != -1 && old_block & c_msb) {
        if (   storage_fd < 0
               || lseek(storage_fd, (old_block ^ c_msb)*BUFFER_SIZE, SEEK_SET) == -1
               || write(storage_fd, _buffer_addr(n), BUFFER_SIZE) == -1
            ) {

            *--sp = -34;
            _abort();
            goto pr_buffer_exit;
        }
    }

    e[ea_buffers + n] = new_block;
    *--sp = _from_ptr(_buffer_addr(n));
    e[ea_next_buffer] = (n + 1) % BUFFER_COUNT;

  pr_buffer_exit:
}
__end
__define_primitive("BUFFER", pr_buffer);
