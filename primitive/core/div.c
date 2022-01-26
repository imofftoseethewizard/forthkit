define_primitive("/", &&pr_div);

#define _div() *++sp = *(sp+1) / *sp

if (0) {
  pr_div:
    _div();
    _next();
}
