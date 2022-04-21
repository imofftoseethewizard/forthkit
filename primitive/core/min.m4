#define _min() *++sp = (number)*(sp+1) > (number)*sp ? *sp : *(sp+1)

__primitive(pr_min)  
{
    _min();
}
__end
__define_primitive("MIN", pr_min);
