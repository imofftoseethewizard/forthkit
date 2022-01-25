define_primitive(">", &&p1_gt);

#define _gt() *++sp = *(sp+1) >  *sp

if (0)
  {
  p1_gt:
    _gt();
    _next();
  }
