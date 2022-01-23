define_primitive("drop", &&p1_drop);

#define _drop() ++sp

if (0)
  {
  p1_drop:
    _drop();
    next();
  }
