
#define _compile_repeat()                          \
    do {                                           \
    _swap();                                       \
    _compile_pr(op_jump);                \
    _store_data((cell *)*sp++ - (cell *)here + 1); \
    _compile_jump_target();                        \
} while (0);

_primitive(pr_compile_repeat) {
    _compile_repeat();
    _next();
}
define_immediate_primitive("REPEAT", pr_compile_repeat);
