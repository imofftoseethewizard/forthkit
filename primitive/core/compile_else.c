define_immediate_primitive("else", &&pr_compile_else);

if (0)
  {
  pr_compile_else:
    /* Jump from here -- the end of the consequent -- to the end of the
       conditional.
     */
    _compile_jump_origin();

    /* Bring the origin of the branch target to the top of the stack
       and point it here, at the begining of the alternate.
     */
    _swap();
    _compile_jump_target();

    _next();
  }
