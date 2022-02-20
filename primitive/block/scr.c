#define _scr() *--sp = _from_ptr(&e[ea_scr])

_primitive(pr_scr) {
    _scr();
    _next();
}
_define_primitive("SCR", pr_scr);
