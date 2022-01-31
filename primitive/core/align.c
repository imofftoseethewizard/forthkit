
_primitive(pr_align) {
    here = (char *)_align(here);
    _next();
}
define_primitive("ALIGN", pr_align);
