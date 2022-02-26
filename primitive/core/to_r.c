_primitive(pr_to_r) {
    *--rp = *sp++;
    _next();
}
_define_primitive(">R", pr_to_r);
