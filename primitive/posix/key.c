
#define _key() *--sp = getc(stdin)

if (0)
  {
  pr_key:
    _key();
    _next();
  }
define_primitive("KEY", pr_key);
