define_primitive("emit", &&p1_emit);

#define _emit() putc(*sp++, stdout)

if (0)
  {
  p1_emit:
    _emit();
    _next();
  }
