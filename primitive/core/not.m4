#define _not() *sp = ~*sp

primitive(pr_not) {
    _not();
    _next();
}
