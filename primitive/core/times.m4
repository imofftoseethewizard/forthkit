#define _times() *++sp = (number)*(sp+1) * (number)*sp

__primitive(pr_times)  
{
    _times();
}
__end
__define_primitive("*", pr_times);
