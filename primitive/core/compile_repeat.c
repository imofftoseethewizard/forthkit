define_immediate_primitive("REPEAT", &&pr_compile_repeat);

#define _compile_repeat()                          \
    do {                                           \
    _swap();                                       \
    _store_data(&&op_jump);                        \
    _store_data((cell *)*sp++ - (cell *)here + 1); \
    _compile_jump_target();                        \
} while (0);

if (0) {
  pr_compile_repeat:
    _compile_repeat();
    _next();
}
