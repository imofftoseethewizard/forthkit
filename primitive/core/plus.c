define_primitive("+", &&pr_plus);

#define _plus() *++sp = *(sp+1) + *sp

if (0) {
  pr_plus:
    _plus();
    _next();
}
