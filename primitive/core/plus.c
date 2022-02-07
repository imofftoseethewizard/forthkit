
#define _plus() *++sp = *(sp+1) + *sp

_primitive(pr_plus) {
    _plus();
    _next();
}
_define_primitive("+", pr_plus);
