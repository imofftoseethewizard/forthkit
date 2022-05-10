#define _div() *++sp = (number)*(sp+1) / (number)*sp

__primitive(pr_div)
{
    if (*sp)
        _div();
    else
        _abort(-10);
}
__end
__define_primitive("/", pr_div);
