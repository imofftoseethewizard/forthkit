
#define _sp_store() sp = (cell *)*sp

_primitive(pr_sp_store) {
    _sp_store();
    _next();
}
define_primitive("SP!", pr_sp_store);
