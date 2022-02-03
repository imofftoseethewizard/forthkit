_primitive(pr_count) {

    register length_type *lenp = (length_type *)_to_native_ptr(*sp);

    *sp = _from_native_ptr(lenp + 1);
    *--sp = *lenp;

    _next();
}
define_primitive("COUNT", pr_count);
