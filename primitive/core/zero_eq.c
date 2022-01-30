define_primitive("0=", pr_zero_eq);

#define _zero_eq() *sp = *sp == 0

if (0) {
  pr_zero_eq:
    _zero_eq();
    _next();
}
