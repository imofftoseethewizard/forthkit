#define _zero_eq() *sp = *sp == 0

__primitive(pr_zero_eq)  
{
    _zero_eq();
}
__end
__define_primitive("0=", pr_zero_eq);
