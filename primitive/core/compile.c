_primitive(pr_compile) {
    *(cell *)here = *ip++;
    _next();
}
_define_primitive("COMPILE", pr_compile);
