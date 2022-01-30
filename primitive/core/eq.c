define_primitive("=", pr_eq);

#define _eq() *++sp = *(sp+1) == *sp

if (0) {
  pr_eq:
    _eq();
    _next();
}
