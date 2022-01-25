define_primitive("NOT", &&pr_not);

#define _not() *sp = ~*sp

if (0)
  {
  pr_not:
    _not();
    _next();
  }
