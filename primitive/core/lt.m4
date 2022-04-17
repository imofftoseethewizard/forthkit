#define _lt() *++sp = (number)*(sp+1) < (number)*sp

primitive(pr_lt) {
    _lt();
    _next();
}
