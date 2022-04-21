#define _fetch() *sp = *_to_ptr(*sp)

__primitive(pr_fetch)  
{
    _fetch();
}
__end
__define_primitive("@", pr_fetch);
