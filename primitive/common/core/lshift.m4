#define _lshift() *++sp = *(sp+1) << *sp

__primitive(pr_lshift)  
{
    _lshift();
}
__end
__define_primitive("lshift", pr_lshift);
