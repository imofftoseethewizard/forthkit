define_primitive("SP0", &&pr_sp0);

#define _sp0() *--sp = (cell)sp0

if (0) {
  pr_sp0:
    _sp0();
    _next();
}
