define_primitive("sp@", &&p1_sp_fetch);

#define _sp_fetch() *--sp = (cell)sp

if (0)
  {
  p1_sp_fetch:
    _sp_fetch();
    next();
  }
