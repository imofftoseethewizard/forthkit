
#define _lt_eq() *++sp = *(sp+1) <= *sp

_primitive(pr_lt_eq) {
    _lt_eq();
    _next();
}
_define_primitive("<=", pr_lt_eq);
