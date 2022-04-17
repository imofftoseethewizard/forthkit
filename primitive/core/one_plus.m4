#define _one_plus() *sp += 1

primitive(pr_one_plus) {
    _one_plus();
    _next();
}
