define_primitive("ALLOT", &&p1_allot);

#define _allot() here += *sp++

if (0)
  {
  p1_allot:
    _allot();
    _next();
  }
