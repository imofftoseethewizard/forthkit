define_primitive("<>", &&pr_neq);

#define _neq() *++sp = *(sp+1) != *sp

if (0)
  {
  pr_neq:
    _neq();
    _next();
  }
