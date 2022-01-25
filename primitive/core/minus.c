define_primitive("-", &&p1_minus);

#define _minus() *++sp = *(sp+1) - *sp

if (0)
  {
  p1_minus:
    _minus();
    _next();
  }
