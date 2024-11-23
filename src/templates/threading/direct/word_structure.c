/*|

  TODO

  |*/

#define _define_primitive_word(name, label, flags)               \
	_info("defining %-16s %lx\n", name, (long)_from_pr(label));  \
	_begin_define_word(name, c_inline | (flags));                \
	_register_compiled_word(cw_ ## label);                       \
	_compile_pr(label);                                          \
	_end_define_word();

/*|

  TODO

  |*/

#define _compile_literal(x)                                      \
	do {                                                         \
		_compile_pr(op_literal);                                 \
		_store_data(x);                                          \
	} while (0)

/*|

  TODO

  |*/

#define _define_constant(s, v)                                   \
	_info("defining constant %-16s %d\n", s, v);                 \
	_begin_define_word(s, c_inline);                             \
	_compile_literal(v);                                         \
	_end_define_word();

/*|

  TODO

  |*/

#define _compile_pw(label) _compile_pr(label)
