
#define _from_tmp() *--sp = *t_sp--

_primitive(pr_from_tmp) {
    _from_tmp();
    _next();
}
define_primitive("T>", pr_from_tmp);
