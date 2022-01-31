
#define _neq() *++sp = *(sp+1) != *sp

_primitive(pr_neq) {
    _neq();
    _next();
}
define_primitive("<>", pr_neq);
