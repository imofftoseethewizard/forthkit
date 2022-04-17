#define _abs() if ((number)*sp < 0) *sp = -(number)*sp;

primitive(pr_abs) {
    _abs();
    _next();
}
