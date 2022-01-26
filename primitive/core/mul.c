define_primitive("*", &&pr_mul);

#define _mul() *++sp = *(sp+1) * *sp

if (0) {
  pr_mul:
    _mul();
    _next();
}
