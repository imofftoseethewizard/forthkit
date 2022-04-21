#define _one_minus() *sp -= 1

__primitive(pr_one_minus)  
{
    _one_minus();
}
__end
__define_primitive("1-", pr_one_minus);
