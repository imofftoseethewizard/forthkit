
#define _eq() *(sp+1) = *(sp+1) == *sp, sp++

_primitive(pr_eq) {
    _eq();
    _next();
}
_define_primitive("=", pr_eq);
