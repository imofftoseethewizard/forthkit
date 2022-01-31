
#define _compile_begin() *--sp = (cell)here

_primitive(pr_compile_begin) {
    _compile_begin();
    _next();
}
define_immediate_primitive("BEGIN", pr_compile_begin);
