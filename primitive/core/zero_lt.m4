#define _zero_lt() *sp = (number)*sp < 0

__primitive(pr_zero_lt)  
{
    _zero_lt();
}
__end
__define_primitive("0<", pr_zero_lt);
