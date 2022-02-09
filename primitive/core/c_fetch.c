_primitive(pr_c_fetch) {
    *sp = *(char *)_to_ptr(*sp);
    _next();
}
_define_primitive("C@", pr_c_fetch);
