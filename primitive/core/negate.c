define_primitive("NEGATE", &&pr_negate);

#define _negate() *sp = ~*sp

if (0) {
  pr_negate:
    _negate();
    _next();
}
