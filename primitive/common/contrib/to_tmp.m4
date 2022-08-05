
#define _to_tmp() *++t_sp = *sp++

__primitive(pr_to_tmp)  
{
    _to_tmp();
}
__end
__define_primitive(">t", pr_to_tmp);
