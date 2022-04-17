#define _dup() *--sp = *(sp+1)

primitive(pr_dup) {
    _dup();
    _next();
}
