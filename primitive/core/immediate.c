
#define _immediate(flags) _set_word_flags(*current, c_immediate)

_primitive(pr_immediate) {
    _immediate();
    _next();
}
define_primitive("IMMEDIATE", pr_immediate);
