define_immediate_primitive("THEN", &&pr_compile_then);

if (0) {
  pr_compile_then:
    _compile_jump_target();
    _next();
}
