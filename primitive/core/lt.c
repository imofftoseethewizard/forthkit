define_primitive("<", &&pr_lt);

#define _lt() *++sp = *(sp+1) <  *sp

if (0)
  {
  pr_lt:
    _lt();
    _next();
  }
