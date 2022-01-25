define_primitive("COUNT", &&pr_count);

#define _count() l = *(char *)sp, (*sp)++, *--sp = l

if (0)
  {
  pr_count:
    _count();
    _next();
  }
