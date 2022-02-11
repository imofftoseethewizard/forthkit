_primitive(pr_compile_do) {
    *--sp = _from_ptr(here);
    _compile_pr(op_do);
    _next();
}
_define_immediate_primitive("DO", pr_compile_do);
