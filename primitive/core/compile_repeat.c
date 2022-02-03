define_immediate_primitive("REPEAT", pr_compile_repeat);

#define _compile_repeat()                                        \
    do {                                                         \
    _swap();                                                     \
    _compile_pr(op_jump);                                        \
    _store_data(*sp++ - _from_native_ptr(here) + sizeof(cell));  \
    _compile_jump_target();                                      \
} while (0);

if (0) {
  pr_compile_repeat:
    _compile_repeat();
    _next();
}
