#define _here() *--sp = _from_ptr(here)

__primitive(pr_here)  
{
    _here();
}
__end
__define_primitive("HERE", pr_here);
