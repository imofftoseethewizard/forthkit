define_primitive("+", &&p1_plus);

#define _plus() *++sp = *(sp+1) + *sp

if (0)
  {
  p1_plus:
    _plus();
    _next();
  }
