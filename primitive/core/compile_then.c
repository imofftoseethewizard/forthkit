define_immediate_primitive("then", &&p1_compile_then);

if (0)
  {
  p1_compile_then:
    _compile_jump_target();
    _next();
  }
