define_primitive("or", &&p1_or);

#define _or() *++sp = *(sp+1) | *sp

if (0)
  {
  p1_or:
    _or();
    _next();
  }
