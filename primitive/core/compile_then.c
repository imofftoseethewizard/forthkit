
#define _compile_then() _compile_jump_target()

_primitive(pr_compile_then) {
    _compile_then();
    _next();
}
_define_immediate_primitive("THEN", pr_compile_then);
