
#define _minus() *++sp = *(sp+1) - *sp

_primitive(pr_minus) {
    _minus();
    _next();
}
define_primitive("-", pr_minus);
