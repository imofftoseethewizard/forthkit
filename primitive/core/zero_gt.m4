#define _zero_gt() *sp = (number)*sp > 0

primitive(pr_zero_gt) {
    _zero_gt();
    _next();
}
