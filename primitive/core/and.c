define_primitive("AND", &&p1_and);

#define _and() *++sp = *(sp+1) & *sp

if (0)
  {
  p1_and:
    _and();
    _next();
  }
