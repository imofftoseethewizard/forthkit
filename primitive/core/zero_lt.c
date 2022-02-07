
#define _zero_lt() *sp = *sp < 0

_primitive(pr_zero_lt) {
    _zero_lt();
    _next();
}
_define_primitive("0<", pr_zero_lt);
