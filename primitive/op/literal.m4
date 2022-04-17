#define _compile_literal(x) do { _compile_pr(op_literal); _store_data(x); } while (0)

primitive(pr_literal) {
    _debug("literal: "); _print_stack();
    _compile_pr(op_literal);
    _store_data(*sp++);
    _next();
}
