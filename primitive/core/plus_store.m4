#define _plus_store() *_to_ptr(*sp) += *(sp+1), sp += 2

__primitive(pr_plus_store)  
{
    _plus_store();
}
__end
__define_primitive("+!", pr_plus_store);
