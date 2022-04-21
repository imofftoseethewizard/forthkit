#define _max() *++sp = (number)*(sp+1) < (number)*sp ? *sp : *(sp+1)

__primitive(pr_max)  
{
    _max();
}
__end
__define_primitive("MAX", pr_max);
