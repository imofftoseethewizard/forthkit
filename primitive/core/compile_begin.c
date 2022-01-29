define_immediate_primitive("BEGIN", &&pr_compile_begin);

#define _compile_begin() *--sp = (cell)here

if (0) {
  pr_compile_begin:
    _compile_begin();
    _next();
}
