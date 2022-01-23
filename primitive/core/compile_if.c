define_immediate_primitive("if", &&p1_compile_if);

if (0)
  {
  p1_compile_if:
    *here++ = (cell)&&op_branch;
    _compile_jump_origin();
    next();
  }
