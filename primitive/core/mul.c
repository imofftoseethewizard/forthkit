define_primitive("*", &&p1_mul);

#define _mul() *++sp = *(sp+1) * *sp

if (0)
  {
  p1_mul:
    _mul();
    _next();
  }
