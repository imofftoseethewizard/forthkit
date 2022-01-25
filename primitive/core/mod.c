define_primitive("%", &&p1_mod);

#define _mod() *++sp = *(sp+1) % *sp

if (0)
  {
  p1_mod:
    _mod();
    _next();
  }
