    /* SPACE ( -- )

       Displays an ASCII space.

       |   : space 32 emit ;
     */
    __compiled_word("SPACE", cw_space, 0)
    _compile_literal(32);
    _compile_pr(pr_emit);
    _compile_pr(op_exit);
