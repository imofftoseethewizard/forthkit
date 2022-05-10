#define _compile_while() \
    do { _compile_pr(op_branch); _compile_jump_origin(); _swap(); } while(0)

__primitive(pr_compile_while)
{
    _compile_while();
    _check_dictionary_bounds();
}
__end
__define_immediate_primitive("WHILE", pr_compile_while);
