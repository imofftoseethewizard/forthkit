define_primitive_ext("LITERAL", pr_literal, c_immediate);

if (0) {
  pr_literal:
    _compile_pr(op_literal);
    _store_data(*sp++);
    _next();
}
