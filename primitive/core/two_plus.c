define_primitive("2+", &&p1_two_plus);

#define _two_plus() *sp += 2

if (0)
  {
  p1_two_plus:
    _two_plus();
    next();
