define_primitive(">", pr_gt);

#define _gt() *++sp = *(sp+1) >  *sp

if (0) {
  pr_gt:
    _gt();
    _next();
}
