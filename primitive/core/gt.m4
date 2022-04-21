#define _gt() *++sp = (number)*(sp+1) >  (number)*sp

__primitive(pr_gt)  
{
    _gt();
}
__end
__define_primitive(">", pr_gt);
