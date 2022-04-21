#define _drop() ++sp

__primitive(pr_drop)  
{
    _drop();
}
__end
__define_primitive("DROP", pr_drop);
