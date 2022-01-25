define_primitive("NEGATE", &&p1_negate);

#define _negate() *sp = ~*sp

if (0)
  {
  p1_negate:
    _negate();
    _next();
  }
