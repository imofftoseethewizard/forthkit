#define _and() *++sp = *(sp+1) & *sp

primitive(pr_and) {
    _and();
    _next();
}
