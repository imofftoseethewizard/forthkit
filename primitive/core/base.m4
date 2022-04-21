#define _base() *--sp = _from_ptr(&e[ea_base])

__primitive(pr_base) 
{
    _base();
}
__end
__define_primitive("BASE", pr_base);
