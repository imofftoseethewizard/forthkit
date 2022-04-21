
#define _sp0() *--sp = (cell)sp0

__primitive(pr_sp0)  
{
    _sp0();
}
__end
__define_primitive("SP0", pr_sp0);
