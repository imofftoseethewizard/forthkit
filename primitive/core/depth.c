_primitive(pr_depth) {
    *--sp = (sp0 - sp)/sizeof(cell);
    _next();
}
_define_primitive("DEPTH", pr_depth);
