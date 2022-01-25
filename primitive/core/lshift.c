define_primitive("<<", &&pr_lshift);

#define _lshift() *++sp = *(sp+1) << *sp

if (0)
  {
  pr_lshift:
    _lshift();
    _next();
  }
