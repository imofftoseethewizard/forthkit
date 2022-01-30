define_primitive("2-", pr_two_minus);

#define _two_minus() *sp -= 2

if (0) {
  pr_two_minus:
    _two_minus();
    _next();
}
