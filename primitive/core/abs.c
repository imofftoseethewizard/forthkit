#define _abs() if ((number)*sp < 0) *sp = -(number)*sp;

_primitive(pr_abs) {
    _abs();
    _next();
}
_define_primitive("ABS", pr_abs);
