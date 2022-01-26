define_primitive("COUNT", &&pr_count);

#define _count() *(sp-1) = *(length_type *)sp, (length_type *)(*sp)++, sp--

if (0) {
  pr_count:
    _count();
    _next();
}
