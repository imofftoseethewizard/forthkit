
#define _to_tmp() *++t_sp = *sp++

_primitive(pr_to_tmp) {
    _to_tmp();
    _next();
}
define_primitive(">T", pr_to_tmp);
