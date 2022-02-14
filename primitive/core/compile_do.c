_primitive(pr_compile_do) {
    _print_stack();
    _compile_pr(op_do);
    *--sp = _from_ptr(here);
    _next();
}
_define_immediate_primitive("DO", pr_compile_do);
