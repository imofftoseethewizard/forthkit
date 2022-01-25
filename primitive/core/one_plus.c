define_primitive("1+", &&p1_one_plus);

#define _one_plus() *sp += 1

if (0)
  {
  p1_one_plus:
    _one_plus();
    _next();
  }
