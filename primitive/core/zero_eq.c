
#define _zero_eq() *sp = *sp == 0

_primitive(pr_zero_eq) {
    _zero_eq();
    _next();
}
define_primitive("0=", pr_zero_eq);
