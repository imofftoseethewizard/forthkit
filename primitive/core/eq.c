define_primitive("=", &&p1_eq);

#define _eq() *++sp = *(sp+1) == *sp

if (0)
  {
  p1_eq:
    _eq();
    next();
  }
