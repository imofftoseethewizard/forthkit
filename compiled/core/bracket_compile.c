_compiled_word("[COMPILE]", c_immediate) {
    _compile_pr(op_literal);
    _store_data(32);
    _compile_pr(pr_word);
    _compile_pr(pr_q_dup);
    _compile_if();
    _compile_pr(pr_find);
    _compile_pr(pr_q_dup);
    _compile_if();
    _compile_pr(pr_store_compiled);
    _compile_else();
    _compile_pr(op_abort);
    _compile_then();
    _compile_else();
    _compile_pr(op_abort);
    _compile_then();
    _compile_pr(op_exit);
}
