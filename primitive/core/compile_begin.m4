#define _compile_begin() *--sp = _from_ptr(dp)

__primitive(pr_compile_begin)  
{
    _compile_begin();
}
__end
__define_immediate_primitive("BEGIN", pr_compile_begin);
