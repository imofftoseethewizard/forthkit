#define _div() *++sp = *(sp+1) / *sp

_primitive(pr_div) {
    _div();
    _next();
}
_define_primitive("/", pr_div);
