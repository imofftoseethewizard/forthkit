
#define _here() *--sp = (cell)here

_primitive(pr_here) {
    _here();
    _next();
}
_define_primitive("HERE", pr_here);
