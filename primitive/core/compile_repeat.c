define_immediate_primitive("REPEAT", &&pr_compile_repeat);

if (0) {
  pr_compile_repeat:
    _swap();
    _store_data(&&op_jump);
    _store_data((cell *)*sp++ - ((cell *)here + 1));
    _compile_jump_target();
}
