
#define _rshift() *++sp = *(sp+1) >> *sp

_primitive(pr_rshift) {
    _rshift();
    _next();
}
define_primitive(">>", pr_rshift);
