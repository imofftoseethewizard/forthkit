#define _lt_eq() *++sp = (number)*(sp+1) <= (number)*sp

__primitive(pr_lt_eq)  
{
    _lt_eq();
}
__end
__define_primitive("<=", pr_lt_eq);
