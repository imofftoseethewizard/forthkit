__primitive(pr_literal)
{
    _debug("literal: "); _print_stack();
    _compile_pr(op_literal);
    _store_data(*sp++);
    _check_dictionary_bounds();
}
__end
__define_primitive_ext("LITERAL", pr_literal, c_immediate);
