define_primitive("IMMEDIATE", &&p1_immediate);

#define _immediate(flags) _set_word_flags(*current, c_immediate)

if (0)
  {
  p1_immediate:
    _immediate();
    _next();
  }
