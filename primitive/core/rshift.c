define_primitive(">>", &&p1_rshift);

#define _rshift() *++sp = *(sp+1) >> *sp

if (0)
  {
  p1_rshift:
    _rshift();
    next();
  }
