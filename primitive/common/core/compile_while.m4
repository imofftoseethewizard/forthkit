#define _compile_while()          \
    do {                          \
        _compile_pr(op_0branch);  \
        *--sp = _from_ptr(dp);    \
        _store_data(0);           \
        _swap();                  \
    } while (0)

__primitive(pr_compile_while)
{
    _compile_while();
    _check_dictionary_bounds();
}
__end
__define_immediate_primitive("while", pr_compile_while);
