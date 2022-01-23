define_primitive("over", &&p1_over);

#define _over() *--sp = *(sp+1)

if (0)
  {
  p1_over:
    _over();
    next();
  }
