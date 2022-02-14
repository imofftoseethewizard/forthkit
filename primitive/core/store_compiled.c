_primitive(pr_store_compiled) {
    register cell xt = *sp;
    register cell *code = _to_ptr(xt);
    register cell flags = *(code - 1);

    if (flags & c_inline)
        _store_data(*code);

    else if (flags & c_value) {

        _store_data(*code);        /* op_literal */
        _store_data(*(code + 1));  /* ...        */

    } else
        _store_data(xt);

    sp++;
    _next();
}

_define_primitive("COMPILE,", pr_store_compiled);
