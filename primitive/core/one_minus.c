define_primitive("1-", &&p1_one_minus);

#define _one_minus() *sp -= 1

if (0)
  {
  p1_one_minus:
    _one_minus();
    _next();
  }
