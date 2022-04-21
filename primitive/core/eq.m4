#define _eq() *(sp+1) = *(sp+1) == *sp, sp++

__primitive(pr_eq)  
{
    _eq();
}
__end
__define_primitive("=", pr_eq);
