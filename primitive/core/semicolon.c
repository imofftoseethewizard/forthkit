_primitive(pr_semicolon) {
    _compile_pr(op_exit);
    e[ea_state] = 0;
    _next();
}

_define_immediate_primitive(";", pr_semicolon);
