define_primitive("here", &&p1_here);

#define _here() *--sp = (cell)here

if (0)
  {
  p1_here:
    _here();
    next();
  }
