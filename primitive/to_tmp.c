define_primitive(">T", pr_to_tmp);

#define _to_tmp() *++t_sp = *sp++

if (0) {
  pr_to_tmp:
    _to_tmp();
    _next();
}
