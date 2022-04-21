#define _and() *++sp = *(sp+1) & *sp

__primitive(pr_and)  
{
    _and();
}
__end
__define_primitive("AND", pr_and);
