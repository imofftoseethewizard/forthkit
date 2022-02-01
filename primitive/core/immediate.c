define_primitive("IMMEDIATE", pr_immediate);

#define _immediate(flags) _set_word_flags(*(cell *)e[ea_current], c_immediate)

if (0) {
  pr_immediate:
    _immediate();
    _next();
}
