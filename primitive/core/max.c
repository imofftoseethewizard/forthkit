define_primitive("MAX", pr_max);

#define _max() *++sp = *(sp+1) < *sp ? *sp : *(sp+1)

if (0) {
  pr_max:
    _max();
    _next();
}
