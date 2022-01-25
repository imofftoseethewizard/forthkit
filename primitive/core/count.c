define_primitive("COUNT", &&p1_count);

#define _count() l = *(char *)sp, (*sp)++, *--sp = l

if (0)
  {
  p1_count:
    _count();
    _next();
  }
