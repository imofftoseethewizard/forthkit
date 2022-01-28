define_immediate_primitive("BEGIN", &&pr_compile_begin);

if (0) {
  pr_compile_begin:
    *--sp = (cell)here;
    _next();
}
