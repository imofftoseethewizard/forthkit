_primitive(pr_context) {
    *--sp = _from_ptr(&e[ea_context]);
    _next();
}
_define_primitive("CONTEXT", pr_context);
