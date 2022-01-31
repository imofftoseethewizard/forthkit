
#define _and() *++sp = *(sp+1) & *sp

_primitive(pr_and) {
    _and();
    _next();
}
define_primitive("AND", pr_and);
