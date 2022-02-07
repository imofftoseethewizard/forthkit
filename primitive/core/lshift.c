
#define _lshift() *++sp = *(sp+1) << *sp

_primitive(pr_lshift) {
    _lshift();
    _next();
}
_define_primitive("<<", pr_lshift);
