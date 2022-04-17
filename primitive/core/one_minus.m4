#define _one_minus() *sp -= 1

primitive(pr_one_minus) {
    _one_minus();
    _next();
}
