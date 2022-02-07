
#define _two_minus() *sp -= 2

_primitive(pr_two_minus) {
    _two_minus();
    _next();
}
_define_primitive("2-", pr_two_minus);
