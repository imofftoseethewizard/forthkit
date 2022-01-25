define_primitive("XOR", &&pr_xor);

#define _xor() *++sp = *(sp+1) ^ *sp

if (0)
  {
  pr_xor:
    _xor();
    _next();
  }
