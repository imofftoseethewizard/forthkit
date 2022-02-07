
#define _or() *++sp = *(sp+1) | *sp

_primitive(pr_or) {
    _or();
    _next();
}
_define_primitive("OR", pr_or);
