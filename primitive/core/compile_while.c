define_immediate_primitive("WHILE", &&pr_compile_while);

#define _compile_while() do { _store_data(&&op_branch); _compile_jump_origin(); } while(0)

if (0) {
  pr_compile_while:
    _compile_while();
    _next();
}
