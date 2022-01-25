define_primitive(">IN", &&pr_to_in);

#define _to_in() *sp-- = (cell)point;

if (0)
  {
  pr_to_in:
    _to_in();
    _next();
  }
