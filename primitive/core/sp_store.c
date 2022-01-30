define_primitive("SP!", pr_sp_store);

#define _sp_store() sp = (cell *)*sp

if (0) {
  pr_sp_store:
    _sp_store();
    _next();
}
