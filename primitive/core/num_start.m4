#define _num_start() *_number_pad_idx_addr() = _c_number_pad_size

primitive(pr_num_start) {
    _num_start();
    _next();
}
