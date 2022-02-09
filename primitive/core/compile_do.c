_primitive(pr_compile_do) {
    *--sp = _from_ptr(here);
    _compile_pr(pr_swap);
    _compile_pr(pr_to_r);
    _compile_pr(pr_to_r);
    _next();
}
_define_immediate_primitive("DO", pr_compile_do);
