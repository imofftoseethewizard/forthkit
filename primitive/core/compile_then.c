define_immediate_primitive("then", &&pr_compile_then);

if (0)
  {
  pr_compile_then:
    _compile_jump_target();
    _next();
  }
