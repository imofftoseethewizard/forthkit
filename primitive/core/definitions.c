_primitive(pr_definitions) {
    e[ea_current] = e[ea_context];
    _next();
}
_define_primitive("DEFINITIONS", pr_definitions);
