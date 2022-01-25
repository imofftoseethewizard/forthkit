define_primitive("DUP", &&p1_dup);

#define _dup() *--sp = *sp

if (0)
  {
  p1_dup:
    _dup();
    _next();
  }
