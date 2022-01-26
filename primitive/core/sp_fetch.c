define_primitive("SP@", &&pr_sp_fetch);

#define _sp_fetch() *--sp = (cell)sp

if (0) {
  pr_sp_fetch:
    _sp_fetch();
    _next();
}
