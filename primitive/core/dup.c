define_primitive("DUP", &&pr_dup);

#define _dup() *--sp = *sp

if (0)
  {
  pr_dup:
    _dup();
    _next();
  }
