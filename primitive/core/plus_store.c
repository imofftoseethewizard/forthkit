define_primitive("+!", &&p1_plus_store);

#define _plus_store() *(*sp++) += *(sp+1)

if (0)
  {
  p1_plus_store:
    _plus_store();
    next();
  }
