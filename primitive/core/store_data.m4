#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#define _store_data(x) *(cell *)dp = (cell)(x), dp += sizeof(cell)

__primitive(pr_store_data)
{
    _store_data(*sp++);
    _check_dictionary_bounds();
}
__end
__define_primitive(`","', pr_store_data);
