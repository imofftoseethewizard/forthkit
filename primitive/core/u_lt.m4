#define _u_lt() *++sp = *(sp+1) < *sp

primitive(pr_u_lt) {
    _u_lt();
    _next();
}
