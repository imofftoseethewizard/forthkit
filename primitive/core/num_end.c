_primitive(pr_num_end) {
    register length_type *idx = (length_type *)here;
    *sp = _from_ptr(here + *idx);
    *--sp = _c_number_pad_size - *idx;
    _next();
}
_define_primitive("#>", pr_num_end);
