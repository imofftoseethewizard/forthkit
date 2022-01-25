define_primitive("roll", &&p1_roll);

#define _roll()                                   \
  tmp0 = *sp, tmp1 = *(sp+tmp0);                  \
  for (i = tmp0; i > 0; i--) *(sp+i) = *(sp+i-1); \
  *++sp = tmp1

if (0)
  {
  p1_roll:
    _roll();
    _next();
  }
