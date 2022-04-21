
#define _sp_store() sp = (cell *)*sp

__primitive(pr_sp_store)  
{
    _sp_store();
}
__end
__define_primitive("SP!", pr_sp_store);
