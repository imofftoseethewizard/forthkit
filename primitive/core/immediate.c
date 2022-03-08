#define _immediate(flags) _set_word_flags(_to_ptr(*_to_ptr(e[ea_current])), c_immediate)

_primitive(pr_immediate) {
    _immediate();
    _next();
}
_define_primitive("IMMEDIATE", pr_immediate);
