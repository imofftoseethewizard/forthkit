    __compiled_word("[COMPILE]", cw_bracket_compile, c_immediate)
    _compile_literal(32);
    _compile_pr(pr_word);
    _compile_pr(pr_q_dup);
    _compile_if();
    _compile_pr(pr_find);
    _compile_pr(pr_q_dup);
    _compile_if();
    _compile_pr(pr_store_compiled);
    _compile_else();
    _compile_literal(-13);
    /* unrecognized word */
    /* https://forth-standard.org/standard/exception */
    _compile_pr(op_abort);
    _compile_then();
    _compile_else();
    _compile_pr(op_abort);
    _compile_then();
    _compile_pr(op_exit);