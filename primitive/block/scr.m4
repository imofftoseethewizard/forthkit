#define _scr() *--sp = _from_ptr(&e[ea_scr])

primitive(pr_scr) {
    _scr();
    _next();
}
