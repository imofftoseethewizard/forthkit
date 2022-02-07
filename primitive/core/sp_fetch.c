
#define _sp_fetch() *--sp = (cell)sp

_primitive(pr_sp_fetch) {
    _sp_fetch();
    _next();
}
_define_primitive("SP@", pr_sp_fetch);
