_compiled_word("SPACE", cw_space, 0) {
    _compile_pr(op_literal);
    _store_data(32);
    _compile_pr(pr_emit);
    _compile_pr(op_exit);
}
