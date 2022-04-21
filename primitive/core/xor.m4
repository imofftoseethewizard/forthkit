#define _xor() *++sp = *(sp+1) ^ *sp

__primitive(pr_xor)  
{
    _xor();
}
__end
__define_primitive("XOR", pr_xor);
