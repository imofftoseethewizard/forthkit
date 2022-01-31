
#define _compile_if() \
    do { _compile_pr(op_branch); _compile_jump_origin(); } while (0)

if (0)  {
  pr_compile_if:
    _compile_if();
    _next();
}
define_immediate_primitive("IF", pr_compile_if);
