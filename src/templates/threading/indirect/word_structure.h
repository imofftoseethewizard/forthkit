/*|

  TODO

  |*/

#define _define_constant(s, v)                                   \
    _info("defining constant %-16s %d\n", s, v);                 \
    _begin_define_word(s, 0);                                    \
    _compile_pr(op_do_var);                                      \
    _store_data(v);                                              \
    _end_define_word();

/*|

  TODO

  |*/

#define _define_primitive_word(name, label, flags)               \
    _info("defining %-16s %lx\n", name, (long)_from_pr(label));  \
    _begin_define_word(name, (flags));                           \
    _register_compiled_word(cw_ ## label);                       \
    _compile_pr(label);                                          \
    _end_define_word();

/*|

  TODO

  |*/

#define _compile_pw(label) _compile_cw(cw_ ## label)

#define _end_compiled_word() _end_define_word()
