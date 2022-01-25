define_immediate_primitive("begin", &&p1_compile_begin);

if (0)
  {
  p1_compile_begin:
    *--sp = (cell)here;
    _next();
  }
