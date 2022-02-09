_primitive(pr_cr) {
    *--sp = 10; /* ASCII line feed */
    *--sp = 13; /* ASCII carriage return */
    _emit();
    _emit();
    _next();
}
_define_primitive("CR", pr_cr);
