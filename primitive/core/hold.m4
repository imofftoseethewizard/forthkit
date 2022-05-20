#define _c_number_pad_size 2 * sizeof(cell) * 8 + 2

#define _number_pad_buf_addr() ((char *)_to_ptr(e[ea_number_pad]) + sizeof(length_type))
#define _number_pad_idx_addr() ((length_type *)_to_ptr(e[ea_number_pad]))

#define _hold(x) \
    *(_number_pad_buf_addr() + --(*_number_pad_idx_addr())) = (x)

__primitive(pr_hold)
{
    _hold(*sp++);
}
__end
__define_primitive("HOLD", pr_hold);
