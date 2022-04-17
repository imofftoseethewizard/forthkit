#define _div() *++sp = (number)*(sp+1) / (number)*sp

primitive(pr_div) {
    if (*sp)
        _div();
    else {
        *--sp = -10;
        _abort();
    }
    _next();
}
