#define _scr() *--sp = _from_ptr(&e[ea_scr])

__primitive(pr_scr)  
{
    _scr();
}
__end
__define_primitive("scr", pr_scr);
