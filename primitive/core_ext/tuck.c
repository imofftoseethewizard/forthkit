define_primitive("TUCK", &&pr_tuck);

#define _tuck() *--sp = *(sp+2)

if (0)
  {
  pr_tuck:
    _tuck();
    _next();
  }
