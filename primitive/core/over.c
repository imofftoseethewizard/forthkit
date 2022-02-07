#define _over() *--sp = *(sp+2)

_primitive(pr_over) {
    _over();
    _next();
}
_define_primitive("OVER", pr_over);
