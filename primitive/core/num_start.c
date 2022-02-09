_primitive(pr_num_start) {
    register length_type *idx = _number_pad_idx_addr();
    *idx = _c_number_pad_size;
    _next();
}
_define_primitive("<#", pr_num_start);
