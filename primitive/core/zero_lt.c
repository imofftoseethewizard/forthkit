define_primitive("0<", &&pr_zero_lt);

#define _zero_lt() *sp = *sp < 0

if (0) {
  pr_zero_lt:
    _zero_lt();
    _next();
}
