_primitive(pr_store_compiled) {
    register cell xt = *sp++;

    if (*(_to_ptr(xt) - 1) & c_inline)
        _store_data(*_to_ptr(xt));
    else
        _store_data(xt);

    _next();
}

_define_primitive("COMPILE,", pr_store_compiled);
