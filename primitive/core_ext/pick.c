define_primitive("pick", &&p1_pick);

#define _pick() *sp-- = *(sp + 1 + *(sp+1))

if (0)
  {
  p1_pick:
    _pick();
    _next();
  }
