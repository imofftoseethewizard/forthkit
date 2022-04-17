#define _compile_then() _compile_jump_target()

primitive(pr_compile_then) {
    _compile_then();
    _next();
}
