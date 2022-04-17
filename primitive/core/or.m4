#define _or() *++sp = *(sp+1) | *sp

primitive(pr_or) {
    _or();
    _next();
}
