#define _compile_if() \
    do { _compile_pr(op_branch); _compile_jump_origin(); } while (0)

primitive(pr_compile_if) {
    _compile_if();
    _next();
}
