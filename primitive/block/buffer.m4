#define _buffer_addr(n) (char *)e + e[ea_size] - e[ea_buffer_size] * ((n) + 1)

__primitive(pr_buffer)
{
    register cell new_block = *sp++;
    register cell n = e[ea_next_buffer];
    register cell old_block = e[e[ea_buffers] + n];

    if (old_block != -1 && old_block & c_msb) {
        if (   storage_fd < 0
               || lseek(storage_fd, (old_block ^ c_msb)*e[ea_buffer_size], SEEK_SET) == -1
               || write(storage_fd, _buffer_addr(n), e[ea_buffer_size]) == -1
            ) {

            _abort(-34);
            goto pr_buffer_exit;
        }
    }

    e[e[ea_buffers] + n] = new_block;
    *--sp = _from_ptr(_buffer_addr(n));
    e[ea_next_buffer] = (n + 1) % BUFFER_COUNT;

  pr_buffer_exit:
}
__end
__define_primitive("BUFFER", pr_buffer);
