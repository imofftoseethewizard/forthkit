_primitive(pr_to_r) {
    *(rp-1) = *rp;
    *rp = *sp++;
    rp--;
    _next();
}
_define_primitive(">R", pr_to_r);
