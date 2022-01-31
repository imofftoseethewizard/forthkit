
#define _negate() *sp = ~*sp

_primitive(pr_negate) {
    _negate();
    _next();
}
define_primitive("NEGATE", pr_negate);
