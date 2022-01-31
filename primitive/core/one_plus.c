
#define _one_plus() *sp += 1

_primitive(pr_one_plus) {
    _one_plus();
    _next();
}
define_primitive("1+", pr_one_plus);
