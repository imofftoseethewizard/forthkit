define_immediate_primitive("while", &&p1_compile_while);

if (0)
  {
  p1_compile_while:
    _store_data(&&op_branch);
    _compile_jump_origin();
    next();
  }
