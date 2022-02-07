
#define _eq() *++sp = *(sp+1) == *sp

_primitive(pr_eq) {
    _eq();
    _next();
}
_define_primitive("=", pr_eq);
