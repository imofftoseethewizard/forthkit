define_primitive("MIN", &&pr_min);

#define _min() *++sp = *(sp+1) > *sp ? *sp : *(sp+1)

if (0)
  {
  pr_min:
    _min();
    _next();
  }
