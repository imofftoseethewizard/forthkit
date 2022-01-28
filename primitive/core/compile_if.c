define_immediate_primitive("IF", &&pr_compile_if);

if (0)  {
  pr_compile_if:
    _store_data(&&op_branch);
    _compile_jump_origin();
    _next();
}
