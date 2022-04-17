#define _lshift() *++sp = *(sp+1) << *sp

primitive(pr_lshift) {
    _lshift();
    _next();
}
