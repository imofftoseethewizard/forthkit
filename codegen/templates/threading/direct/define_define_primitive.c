#define _define_primitive(name, label, flags)                        \
        _info("defining %-16s %lx\n", name, (long)_from_pr(label));  \
        _begin_define_word(name, (flags));                           \
        _register_compiled_word(cw_ ## label);                       \
        _compile_pr(label);                                          \
        _compile_pr(op_exit);                                        \
        _end_define_word();
