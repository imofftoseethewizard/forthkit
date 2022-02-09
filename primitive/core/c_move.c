_primitive(pr_c_move) {
    memcpy(_to_ptr(*(sp+1)), _to_ptr(*(sp+2)), *sp);
    sp += 3;
    _next();
}
_define_primitive("CMOVE", pr_c_move);
