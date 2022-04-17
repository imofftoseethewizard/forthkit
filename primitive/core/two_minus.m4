#define _two_minus() *sp -= 2

primitive(pr_two_minus) {
    _two_minus();
    _next();
}
