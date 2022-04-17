
#define _sp_store() sp = (cell *)*sp

primitive(pr_sp_store) {
    _sp_store();
    _next();
}
_define_primitive("SP!", pr_sp_store);
