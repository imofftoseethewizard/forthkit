define_primitive("2DROP", pr_drop2);

#define _drop2() sp += 2

if (0) {
  pr_drop2:
    _drop2();
    _next();
}
