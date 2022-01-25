define_primitive("TUCK", &&p1_tuck);

#define _tuck() *--sp = *(sp+2)

if (0)
  {
  p1_tuck:
    _tuck();
    _next();
  }
