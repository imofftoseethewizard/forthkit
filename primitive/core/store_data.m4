#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#define _store_data(x)                                                     \
     here = (char *)_align(here), *(cell *)here = (cell)(x), here += sizeof(cell)

__primitive(pr_store_data)  
{
    _store_data(*sp++);
}
__end
__define_primitive(`","', pr_store_data);
