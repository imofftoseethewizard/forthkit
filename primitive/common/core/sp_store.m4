
#define _sp_store() sp = (cell *)*sp

__primitive(pr_sp_store)  
{
    _sp_store();
}
__end
__define_primitive("sp!", pr_sp_store);
