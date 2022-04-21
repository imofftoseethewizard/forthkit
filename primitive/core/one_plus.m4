#define _one_plus() *sp += 1

__primitive(pr_one_plus)  
{
    _one_plus();
}
__end
__define_primitive("1+", pr_one_plus);
