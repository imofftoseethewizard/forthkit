define_primitive("2+", &&pr_two_plus);

#define _two_plus() *sp += 2

if (0)
  {
  pr_two_plus:
    _two_plus();
    _next();
