#define _two_minus() *sp -= 2

__primitive(pr_two_minus)  
{
    _two_minus();
}
__end
__define_primitive("2-", pr_two_minus);
