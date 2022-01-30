define_primitive("1-", pr_one_minus);

#define _one_minus() *sp -= 1

if (0) {
  pr_one_minus:
    _one_minus();
    _next();
}
