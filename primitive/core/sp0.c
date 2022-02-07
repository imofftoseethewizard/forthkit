
#define _sp0() *--sp = (cell)sp0

_primitive(pr_sp0) {
    _sp0();
    _next();
}
_define_primitive("SP0", pr_sp0);
