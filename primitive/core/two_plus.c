
#define _two_plus() *sp += 2

_primitive(pr_two_plus) {
    _two_plus();
    _next();
}
_define_primitive("2+", pr_two_plus);
