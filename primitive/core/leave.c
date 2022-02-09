_primitive(pr_leave) {
    *(rp+1) = *rp;
    _next();
}
_define_primitive("LEAVE", pr_leave);
