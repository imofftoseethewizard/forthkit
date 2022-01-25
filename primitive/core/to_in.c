define_primitive(">in", &&p1_to_in);

#define _to_in() *sp-- = (cell)point;

if (0)
  {
  p1_to_in:
    _to_in();
    _next();
  }
