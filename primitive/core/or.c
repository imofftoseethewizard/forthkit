
#define _or() *++sp = *(sp+1) | *sp

_primitive(pr_or) {
    _or();
    _next();
}
define_primitive("OR", pr_or);
