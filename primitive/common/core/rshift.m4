#define _rshift() *++sp = *(sp+1) >> *sp

__primitive(pr_rshift)  
{
    _rshift();
}
__end
__define_primitive("RSHIFT", pr_rshift);
