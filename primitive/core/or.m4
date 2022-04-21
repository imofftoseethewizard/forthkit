#define _or() *++sp = *(sp+1) | *sp

__primitive(pr_or)  
{
    _or();
}
__end
__define_primitive("OR", pr_or);
