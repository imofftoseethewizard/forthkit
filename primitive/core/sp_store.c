define_primitive("SP!", &&p1_sp_store);

#define _sp_store() sp = (cell *)*sp

if (0)
  {
  p1_sp_store:
    _sp_store();
    _next();
  }
