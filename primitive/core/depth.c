_primitive(pr_depth) {
    *--sp = sp0 - sp;
    _next();
}
_define_primitive("DEPTH", pr_depth);
