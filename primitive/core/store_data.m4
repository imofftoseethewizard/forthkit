#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#define _store_data(x)                                                     \
     here = (char *)_align(here), *(cell *)here = (cell)(x), here += sizeof(cell)

primitive(pr_store_data) {
    _store_data(*sp++);
    _next();
}
