define_primitive("-", pr_minus);

#define _minus() *++sp = *(sp+1) - *sp

if (0) {
  pr_minus:
    _minus();
    _next();
}
