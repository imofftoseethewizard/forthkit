#define _c_number_pad_size 2 * sizeof(cell) * 8 + 2

#define _number_pad_buf_addr() ((char *)e + e[ea_size] - BUFFER_COUNT * e[ea_buffer_size] - _c_number_pad_size)
#define _number_pad_idx_addr() ((length_type *)(_number_pad_buf_addr() - sizeof(length_type)))

#define _hold(x) \
    *(_number_pad_buf_addr() + --(*_number_pad_idx_addr())) = (x)

__primitive(pr_hold)  
{
    _hold(*sp++);
}
__end
__define_primitive("HOLD", pr_hold);
