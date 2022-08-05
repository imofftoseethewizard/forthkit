
#define _from_tmp() *--sp = *t_sp--

__primitive(pr_from_tmp)  
{
    _from_tmp();
}
__end
__define_primitive("t>", pr_from_tmp);
