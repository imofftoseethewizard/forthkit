#define _not() *sp = ~*sp

__primitive(pr_not)  
{
    _not();
}
__end
__define_primitive("NOT", pr_not);
