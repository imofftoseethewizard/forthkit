define_primitive("OVER", &&pr_over);

#define _over() *--sp = *(sp+1)

if (0)
  {
  pr_over:
    _over();
    _next();
  }
