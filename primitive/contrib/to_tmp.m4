
#define _to_tmp() *++t_sp = *sp++

primitive(pr_to_tmp) {
    _to_tmp();
    _next();
}
_define_primitive(">T", pr_to_tmp);
