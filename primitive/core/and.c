define_primitive("AND", pr_and);

#define _and() *++sp = *(sp+1) & *sp

if (0) {
  pr_and:
    _and();
    _next();
}
