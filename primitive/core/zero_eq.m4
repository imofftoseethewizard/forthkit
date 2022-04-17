#define _zero_eq() *sp = *sp == 0

primitive(pr_zero_eq) {
    _zero_eq();
    _next();
}
