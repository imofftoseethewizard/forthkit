    __compiled_word("SPACES", cw_spaces, 0)
    _compile_literal(0);
    _compile_pr(op_do);
    *--sp = _from_ptr(dp);
    _compile_literal(32);
    _compile_pr(pr_emit);
    _compile_pr(op_loop);
    _compile_pr(op_jump);
    _store_data((char *)_to_ptr(*sp++) - dp + sizeof(cell));
    _compile_pr(op_exit);

