define_primitive("t>", &&p1_from_tmp);

#define _from_tmp() *--sp = *t_sp--

if (0)
  {
  p1_from_tmp:
    _from_tmp();
    next();
  }
