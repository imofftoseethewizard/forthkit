define_primitive("sp0", &&p1_sp0);

#define _sp0() *--sp = (cell)sp0

if (0)
  {
  p1_sp0:
    _sp0();
    next();
  }
