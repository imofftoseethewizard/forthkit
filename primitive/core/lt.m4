#define _lt() *++sp = (number)*(sp+1) < (number)*sp

__primitive(pr_lt)  
{
    _lt();
}
__end
__define_primitive("<", pr_lt);
