#define _immediate(flags) _set_word_flags(_to_ptr(*_to_ptr(e[ea_current])), c_immediate)

primitive(pr_immediate) {
    _immediate();
    _next();
}
