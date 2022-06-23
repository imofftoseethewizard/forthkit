#define _plus() *(number *)(sp+1) = (number)*(sp+1) + (number)*sp, sp++

__primitive(pr_plus)  
{
    _plus();
}
__end
__define_primitive("+", pr_plus);
