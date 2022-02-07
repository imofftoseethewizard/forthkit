
#define _negate() *sp = ~*sp

_primitive(pr_negate) {
    _negate();
    _next();
}
_define_primitive("NEGATE", pr_negate);
