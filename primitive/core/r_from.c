_primitive(pr_r_from) {
    *--sp = *rp++;
    _next();
}
_define_primitive("R>", pr_r_from);
