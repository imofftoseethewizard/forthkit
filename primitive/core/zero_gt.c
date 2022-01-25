define_primitive("0>", &&p1_zero_gt);

#define _zero_gt() *sp = *sp > 0

if (0)
  {
  p1_zero_gt:
    _zero_gt();
    _next();
  }
