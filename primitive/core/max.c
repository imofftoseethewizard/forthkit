define_primitive("max", &&p1_max);

#define _max() *++sp = *(sp+1) < *sp ? *sp : *(sp+1)

if (0)
  {
  p1_max:
    _max();
    next();
  }
