define_primitive("<", &&p1_lt);

#define _lt() *++sp = *(sp+1) <  *sp

if (0)
  {
  p1_lt:
    _lt();
    next();
  }
