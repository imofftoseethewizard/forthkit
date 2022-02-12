_primitive(pr_store_compiled) {
    _store_data(*sp++);
    _next();
}

_define_primitive("COMPILE,", pr_store_compiled);
