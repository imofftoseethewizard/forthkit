define_primitive(">>", &&pr_rshift);

#define _rshift() *++sp = *(sp+1) >> *sp

if (0) {
  pr_rshift:
    _rshift();
    _next();
}
