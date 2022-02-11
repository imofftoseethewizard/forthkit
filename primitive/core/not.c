#define _not() *sp = ~*sp

_primitive(pr_not) {
    _not();
    _next();
}
_define_primitive("NOT", pr_not);
