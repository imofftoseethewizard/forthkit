
#define _compile_begin() *--sp = _from_ptr(here)

_primitive(pr_compile_begin) {
    _compile_begin();
    _next();
}
_define_immediate_primitive("BEGIN", pr_compile_begin);
