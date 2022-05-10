#define _compile_if() \
    do { _compile_pr(op_branch); _compile_jump_origin(); } while (0)

__primitive(pr_compile_if)
{
    _compile_if();
    _check_dictionary_bounds();
}
__end
__define_immediate_primitive("IF", pr_compile_if);
