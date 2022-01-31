
#define _compile_while() \
    do { _compile_pr(op_branch); _compile_jump_origin(); } while(0)

_primitive(pr_compile_while) {
    _compile_while();
    _next();
}
define_immediate_primitive("WHILE", pr_compile_while);
