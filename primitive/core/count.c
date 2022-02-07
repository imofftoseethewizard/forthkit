_primitive(pr_count) {

    register length_type *lenp = (length_type *)_to_ptr(*sp);

    *sp = _from_ptr(lenp + 1);
    *--sp = *lenp;

    _next();
}
_define_primitive("COUNT", pr_count);
