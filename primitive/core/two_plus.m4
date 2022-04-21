#define _two_plus() *sp += 2


__primitive(pr_two_plus)  
{
    _two_plus();
}
__end
__define_primitive("2+", pr_two_plus);
