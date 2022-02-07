
#define _compile_if() \
    do { _compile_pr(op_branch); _compile_jump_origin(); } while (0)

_primitive(pr_compile_if) {
    _compile_if();
    _next();
}
_define_immediate_primitive("IF", pr_compile_if);
