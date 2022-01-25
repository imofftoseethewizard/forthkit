define_primitive("SWAP", &&pr_swap);

#define _swap() tmp0 = *sp, *sp = *(sp+1), *(sp+1) = tmp0

if (0)
  {
  pr_swap:
    _swap();
    _next();
  }
