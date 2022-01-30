define_primitive("IMMEDIATE", pr_immediate);

#define _immediate(flags) _set_word_flags(*current, c_immediate)

if (0) {
  pr_immediate:
    _immediate();
    _next();
}
