#define _rshift() *++sp = *(sp+1) >> *sp

primitive(pr_rshift) {
    _rshift();
    _next();
}
