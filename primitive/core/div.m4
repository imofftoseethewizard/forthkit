#define _div() *++sp = (number)*(sp+1) / (number)*sp

__primitive(pr_div)
{
    if (*sp)
        _div();
    else
        _abort(err_division_by_zero);
}
__end
__define_primitive("/", pr_div);
