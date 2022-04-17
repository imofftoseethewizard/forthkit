#define _compile_repeat()                                 \
    do {                                                  \
    _compile_pr(op_jump);                                 \
    _store_data(*sp++ - _from_ptr(here) + sizeof(cell));  \
    _compile_jump_target();                               \
} while (0);

primitive(pr_compile_repeat) {
    _compile_repeat();
    _next();
}
