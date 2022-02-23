#define _lt() *++sp = (number)*(sp+1) < (number)*sp

_primitive(pr_lt) {
    _lt();
    _next();
}
_define_primitive("<", pr_lt);
