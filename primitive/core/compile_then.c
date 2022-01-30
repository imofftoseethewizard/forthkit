define_immediate_primitive("THEN", pr_compile_then);

#define _compile_then() _compile_jump_target()

if (0) {
  pr_compile_then:
    _compile_then();
    _next();
}
