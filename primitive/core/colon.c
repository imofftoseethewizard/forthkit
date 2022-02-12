_primitive(pr_colon) {

    register cell name = _from_ptr(here);
    register cell *string_addr = _to_ptr(*sp);
    register length_type n = *(length_type *)string_addr;

    memcpy(here, string_addr, n + sizeof(length_type));
    here += n + sizeof(length_type);

    *sp = name;
    e[ea_context] = e[ea_current];

    _word_header(0);

    e[ea_state] = 1;

    _next();
}

_define_parsing_primitive(":", pr_colon);
