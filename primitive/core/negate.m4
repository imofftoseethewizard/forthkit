#define _negate() *sp = -(number)*sp

primitive(pr_negate) {
    _negate();
    _next();
}
