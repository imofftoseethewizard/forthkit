#define _negate() *sp = -(number)*sp

__primitive(pr_negate)  
{
    _negate();
}
__end
__define_primitive("NEGATE", pr_negate);
