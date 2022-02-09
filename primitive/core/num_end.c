_primitive(pr_num_end) {
    register length_type *idx = _number_pad_idx_addr();
    register char *chp = _number_pad_buf_addr();
    *sp = _from_ptr(chp + *idx);
    *--sp = _c_number_pad_size - *idx;
    _next();
}
_define_primitive("#>", pr_num_end);
