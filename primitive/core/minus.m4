#define _minus() *++sp = *(sp+1) - *sp

primitive(pr_minus) {
    _minus();
    _next();
}
