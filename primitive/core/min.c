define_primitive("MIN", &&p1_min);

#define _min() *++sp = *(sp+1) > *sp ? *sp : *(sp+1)

if (0)
  {
  p1_min:
    _min();
    _next();
  }
