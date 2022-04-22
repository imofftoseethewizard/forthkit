    __compiled_word("WORD", cw_word, 0)
    _compile_literal(MAX_WORD_LENGTH);
    _compile_pr(pr_allot);
    _compile_pr(pr_word);
    _compile_literal(-MAX_WORD_LENGTH);
    _compile_pr(pr_allot);
    _compile_pr(op_exit);

