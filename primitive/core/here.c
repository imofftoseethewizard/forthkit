define_primitive("HERE", &&pr_here);

#define _here() *--sp = (cell)here

if (0) {
  pr_here:
    _here();
    _next();
}
