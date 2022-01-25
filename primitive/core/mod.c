define_primitive("%", &&pr_mod);

#define _mod() *++sp = *(sp+1) % *sp

if (0)
  {
  pr_mod:
    _mod();
    _next();
  }
