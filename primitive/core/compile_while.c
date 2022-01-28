define_immediate_primitive("WHILE", &&pr_compile_while);

if (0) {
  pr_compile_while:
    _store_data(&&op_branch);
    _compile_jump_origin();
    _next();
}
