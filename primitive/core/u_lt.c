#define _u_lt() *++sp = *(sp+1) < *sp

_primitive(pr_u_lt) {
    _u_lt();
    _next();
}
_define_primitive("U<", pr_u_lt);
