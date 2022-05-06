#define _here() *--sp = _from_ptr(dp)

__primitive(pr_here)  
{
    _here();
}
__end
__define_primitive("HERE", pr_here);
