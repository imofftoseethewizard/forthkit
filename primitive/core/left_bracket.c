_primitive(pr_left_bracket) {
    e[ea_state] = 0;
    _next();
}

_define_immediate_primitive("[", pr_left_bracket);
