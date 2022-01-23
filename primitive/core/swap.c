define_primitive("swap", &&p1_swap);

#define _swap() tmp0 = *sp, *sp = *(sp+1), *(sp+1) = tmp0

if (0)
  {
  p1_swap:
    _swap();
    next();
  }
