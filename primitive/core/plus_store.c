define_primitive("+!", &&pr_plus_store);

#define _plus_store() *(*sp++) += *(sp+1)

if (0)
  {
  pr_plus_store:
    _plus_store();
    _next();
  }
