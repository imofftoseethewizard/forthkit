
#define _zero_gt() *sp = *sp > 0

_primitive(pr_zero_gt) {
    _zero_gt();
    _next();
}
_define_primitive("0>", pr_zero_gt);
