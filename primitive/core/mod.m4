#define _mod() *++sp = (number)*(sp+1) % (number)*sp

__primitive(pr_mod)  
{
    _mod();
}
__end
__define_primitive("MOD", pr_mod);
