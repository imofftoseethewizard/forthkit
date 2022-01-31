
#define _mul() *++sp = *(sp+1) * *sp

_primitive(pr_mul) {
    _mul();
    _next();
}
define_primitive("*", pr_mul);
