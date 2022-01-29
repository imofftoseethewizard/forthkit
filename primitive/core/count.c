define_primitive("COUNT", &&pr_count);

#define _count() *(sp-1) = *(length_type *)*sp, *sp-- = (cell)((length_type *)*sp + 1)

if (0) {
  pr_count:
    _count();
    print_stack(sp0, sp);
    _next();
}
