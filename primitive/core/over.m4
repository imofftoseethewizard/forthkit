#define _over() *--sp = *(sp+2)

__primitive(pr_over)  
{
    _over();
}
__end
__define_primitive("OVER", pr_over);
