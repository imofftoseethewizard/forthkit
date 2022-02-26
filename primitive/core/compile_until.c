#define _compile_until()                                      \
    do {                                                      \
        _compile_pr(op_branch);                               \
        _compile_pr(op_jump);                                 \
        _store_data(*sp++ - _from_ptr(here) + sizeof(cell));  \
    } while (0);

_primitive(pr_compile_until) {
    _compile_until();
    _next();
}
_define_immediate_primitive("UNTIL", pr_compile_until);
