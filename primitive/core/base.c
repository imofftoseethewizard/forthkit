#define _base() *--sp = _from_ptr(&e[ea_base])

_primitive(pr_base) {
    _base();
    _next();
}
_define_primitive("BASE", pr_base);
