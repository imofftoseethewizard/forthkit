define_primitive("nip", &&p1_nip);

#define _nip() *++sp = *(sp-1)

if (0)
  {
  p1_nip:
      _nip();
      next();
  }
