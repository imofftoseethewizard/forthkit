_primitive(pr_abort) {
    _execute(_pr_addr(op_abort));
}

define_primitive("ABORT", pr_abort)
