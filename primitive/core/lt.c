
#define _lt() *++sp = *(sp+1) <  *sp

_primitive(pr_lt) {
    _lt();
    _next();
}
define_primitive("<", pr_lt);
