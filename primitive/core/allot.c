define_primitive("ALLOT", pr_allot);

#define _allot() here += *sp++

if (0) {
  pr_allot:
    _allot();
    _next();
}
