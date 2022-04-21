
#define _neq() *++sp = *(sp+1) != *sp

__primitive(pr_neq)  
{
    _neq();
}
__end
__define_primitive("<>", pr_neq);
