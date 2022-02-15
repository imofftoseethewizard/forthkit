_compiled_word("SPACES", 0) {
    _compile_pr(op_literal);
    _store_data(0);
    _compile_pr(op_do);
    *--sp = _from_ptr(here);
    _compile_pr(op_literal);
    _store_data(32);
    _compile_pr(pr_emit);
    _compile_pr(op_loop);
    _compile_pr(op_jump);
    _store_data((char *)_to_ptr(*sp++) - here + sizeof(cell));
    _compile_pr(op_exit);
}
