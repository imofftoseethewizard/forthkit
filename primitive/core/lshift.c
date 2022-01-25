define_primitive("<<", &&p1_lshift);

#define _lshift() *++sp = *(sp+1) << *sp

if (0)
  {
  p1_lshift:
    _lshift();
    _next();
  }
