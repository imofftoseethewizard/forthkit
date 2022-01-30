define_primitive("T>", pr_from_tmp);

#define _from_tmp() *--sp = *t_sp--

if (0) {
  pr_from_tmp:
    _from_tmp();
    _next();
}
