define_primitive("NOT", &&p1_not);

#define _not() *sp = ~*sp

if (0)
  {
  p1_not:
    _not();
    _next();
  }
