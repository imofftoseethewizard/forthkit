#define _div() *++sp = (number)*(sp+1) / (number)*sp

__primitive(pr_div)  
{
    if (*sp)
        _div();
    else {
        *--sp = -10;
        _abort();
    }
}
__end
__define_primitive("/", pr_div);
