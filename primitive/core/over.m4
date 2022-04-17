#define _over() *--sp = *(sp+2)

primitive(pr_over) {
    _over();
    _next();
}
