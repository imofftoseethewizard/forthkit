_primitive(pr_r_from) {
    *--sp = *(rp+1);
    *(rp+1) = *rp;
    rp++;
    _next();
}
_define_primitive("R>", pr_r_from);
