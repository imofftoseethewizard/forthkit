#define _div() *++sp = *(sp+1) / *sp

_primitive(pr_div) {
    if (*sp)
        _div();
    else {
        *--sp = -10;
        _abort();
    }
    _next();
}
_define_primitive("/", pr_div);
