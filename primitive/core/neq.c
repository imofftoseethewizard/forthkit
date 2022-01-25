define_primitive("<>", &&p1_neq);

#define _neq() *++sp = *(sp+1) != *sp

if (0)
  {
  p1_neq:
    _neq();
    _next();
  }
