
#define _drop2() sp += 2

__primitive(pr_drop2)  
{
    _drop2();
}
__end
__define_primitive("2DROP", pr_drop2);
