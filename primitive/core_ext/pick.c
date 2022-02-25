_primitive(pr_pick) {
    register number n = *sp;
    if (n >= 1)
        *sp = *(sp + n);
    else {
        *sp = -24; /* invalid numeric argument */
        _abort();
    }
    _next();
}

_define_primitive("PICK", pr_pick);
