define_primitive("EMIT", &&pr_emit);

#define _emit() putc(*sp++, stdout)

if (0)
  {
  pr_emit:
    _emit();
    _next();
  }
