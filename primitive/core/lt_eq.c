define_primitive("<=", &&pr_lt_eq);

#define _lt_eq() *++sp = *(sp+1) <= *sp

if (0)
  {
  pr_lt_eq:
    _lt_eq();
    _next();
  }
