#define _div() *++sp = (number)*(sp+1) / (number)*sp

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
