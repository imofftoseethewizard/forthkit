define_primitive("@", &&p1_fetch);

#define _fetch() *sp = *(cell *)(*sp)

if (0)
  {
  p1_fetch:
    _fetch();
    _next();

  }
