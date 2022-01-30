define_primitive("OR", pr_or);

#define _or() *++sp = *(sp+1) | *sp

if (0) {
  pr_or:
    _or();
    _next();
}
