define_primitive("not", &&p1_not);

#define _not() *sp = ~*sp

if (0)
  {
  p1_not:
    _not();
    next();
  }
