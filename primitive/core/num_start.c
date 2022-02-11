#define _num_start() *_number_pad_idx_addr() = _c_number_pad_size

_primitive(pr_num_start) {
    _num_start();
    _next();
}
_define_primitive("<#", pr_num_start);
