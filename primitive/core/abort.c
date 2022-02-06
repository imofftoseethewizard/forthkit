_primitive(pr_abort) {
    _abort();
    _next();
}

define_primitive("ABORT", pr_abort)
