#define _dup() *--sp = *(sp+1)

__primitive(pr_dup)  
{
    _dup();
}
__end
__define_primitive("DUP", pr_dup);
