_primitive(pr_div) {
    if (*sp)
        _div();
    else {
        *--sp = -10;
        _abort();
    }
    _next();
}
