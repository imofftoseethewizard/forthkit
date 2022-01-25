define_primitive("XOR", &&p1_xor);

#define _xor() *++sp = *(sp+1) ^ *sp

if (0)
  {
  p1_xor:
    _xor();
    _next();
  }
