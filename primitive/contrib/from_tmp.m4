
#define _from_tmp() *--sp = *t_sp--

primitive(pr_from_tmp) {
    _from_tmp();
    _next();
}
_define_primitive("T>", pr_from_tmp);
