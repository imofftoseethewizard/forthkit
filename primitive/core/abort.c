_primitive(pr_abort) {
    _abort();
    _next();
}

_define_primitive("ABORT", pr_abort)
