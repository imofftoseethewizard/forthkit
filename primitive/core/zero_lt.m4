#define _zero_lt() *sp = (number)*sp < 0

primitive(pr_zero_lt) {
    _zero_lt();
    _next();
}
