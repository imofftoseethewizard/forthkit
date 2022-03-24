_primitive(pr_literal) {
    _debug("literal: "); _print_stack();
    _compile_pr(op_literal);
    _store_data(*sp++);
    _next();
}
