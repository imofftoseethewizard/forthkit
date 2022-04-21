
#define _sp_fetch() *--sp = (cell)sp

__primitive(pr_sp_fetch)  
{
    _sp_fetch();
}
__end
__define_primitive("SP@", pr_sp_fetch);
