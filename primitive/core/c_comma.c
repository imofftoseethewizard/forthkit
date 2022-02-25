_primitive(pr_c_comma) {
    *here++ = (char)*sp++;
    _next();
}
_define_primitive("C,", pr_c_comma);
