
#define _lt() *++sp = *(sp+1) <  *sp

_primitive(pr_lt) {
    _lt();
    _next();
}
_define_primitive("<", pr_lt);
