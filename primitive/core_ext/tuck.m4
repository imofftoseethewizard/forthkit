
#define _tuck() *--sp = *(sp+2)

__primitive(pr_tuck)  
{
    _tuck();
}
__end
__define_primitive("TUCK", pr_tuck);
