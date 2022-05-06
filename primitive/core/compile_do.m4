#define _compile_do() do { _compile_pr(op_do); *--sp = _from_ptr(dp); } while (0)

__primitive(pr_compile_do)  
{
    _compile_do();
}
__end
__define_immediate_primitive("DO", pr_compile_do);
