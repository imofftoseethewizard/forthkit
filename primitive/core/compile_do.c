#define _compile_do() do { _compile_pr(op_do); *--sp = _from_ptr(here); } while (0)

_primitive(pr_compile_do) {
    _compile_do();
    _next();
}
_define_immediate_primitive("DO", pr_compile_do);
