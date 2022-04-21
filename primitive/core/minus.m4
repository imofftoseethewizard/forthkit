#define _minus() *++sp = *(sp+1) - *sp

__primitive(pr_minus)  
{
    _minus();
}
__end
__define_primitive("-", pr_minus);
