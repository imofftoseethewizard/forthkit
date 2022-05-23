__primitive(pr_semicolon)
{
    _compile_pr(op_exit);
    tp[ta_state] = 0;
    _check_dictionary_bounds();
}
__end
__define_immediate_primitive(";", pr_semicolon);
