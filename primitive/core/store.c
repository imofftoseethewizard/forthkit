define_primitive("!", &&p1_store);

#define _store() *(cell *)*sp = *(sp+1), sp += 2

if (0)
  {
  p1_store:
    _store();
    _next();
  }
