#define _abs() if ((number)*sp < 0) *sp = -(number)*sp;

__primitive(pr_abs)  
{
    _abs();
}
__end
__define_primitive("ABS", pr_abs);
