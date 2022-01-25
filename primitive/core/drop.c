define_primitive("DROP", &&pr_drop);

#define _drop() ++sp

if (0)
  {
  pr_drop:
    _drop();
    _next();
  }
