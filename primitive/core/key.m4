#define _key() *--sp = getc(stdin)

__primitive(pr_key)  
{
    _key();
}
__end
__define_primitive("KEY", pr_key);
