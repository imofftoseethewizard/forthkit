
#define _eq() *++sp = *(sp+1) == *sp

_primitive(pr_eq) {
    _eq();
    _next();
}
define_primitive("=", pr_eq);
