#define _base() *--sp = _from_ptr(&e[ea_base])

primitive(pr_base) {
    _base();
    _next();
}
