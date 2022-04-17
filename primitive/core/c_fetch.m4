primitive(pr_c_fetch) {
    *sp = *(char *)_to_ptr(*sp);
    _next();
}
