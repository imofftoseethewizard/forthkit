define_primitive("/", &&p1_div);

#define _div() *++sp = *(sp+1) / *sp

if (0)
  {
  p1_div:
    _div();
    next();
  }
