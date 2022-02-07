
#define _one_minus() *sp -= 1

_primitive(pr_one_minus) {
    _one_minus();
    _next();
}
_define_primitive("1-", pr_one_minus);
