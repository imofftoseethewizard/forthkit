#define _num_end()                                       \
do {                                                     \
    register length_type *idx = _number_pad_idx_addr();  \
    register char *chp = _number_pad_buf_addr();         \
    *(sp+1) = _from_ptr(chp + *idx);                     \
    *sp = _c_number_pad_size - *idx;                     \
} while (0)

_primitive(pr_num_end) {
    _num_end();
    _next();
}

_define_primitive("#>", pr_num_end);
