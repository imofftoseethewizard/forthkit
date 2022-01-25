define_primitive("DROP", &&p1_drop);

#define _drop() ++sp

if (0)
  {
  p1_drop:
    _drop();
    _next();
  }
