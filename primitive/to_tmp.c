define_primitive(">t", &&p1_to_tmp);

#define _to_tmp() *++t_sp = *sp++

if (0) {
  p1_to_tmp:
    _to_tmp();
    _next();
 }
