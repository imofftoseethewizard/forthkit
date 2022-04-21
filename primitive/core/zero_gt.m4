#define _zero_gt() *sp = (number)*sp > 0

__primitive(pr_zero_gt)  
{
    _zero_gt();
}
__end
__define_primitive("0>", pr_zero_gt);
