_primitive(pr_forth) {
    e[ea_context] = _from_ptr(&e[ea_forth]);
    _next();
}

_define_primitive("FORTH", pr_forth);
