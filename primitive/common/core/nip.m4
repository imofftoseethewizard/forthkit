
#define _nip() *++sp = *(sp-1)

__primitive(pr_nip)  
{
    _nip();
}
__end
__define_primitive("nip", pr_nip);
