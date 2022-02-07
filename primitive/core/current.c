_primitive(pr_current) {
    *--sp = _from_ptr(&e[ea_current]);
    _next();
}
_define_primitive("CURRENT", pr_current);
