
    /* SPACES ( n -- )
       Display n ASCII spaces. Take no action for n of zero or less.

       |   : spaces
       |       0 do
       |           32 emit
       |       loop
       |   ;
     */
    __compiled_word("SPACES", cw_spaces, 0)

    _compile_literal(0);
    _compile_do();

    _compile_literal(32);
    _compile_pr(pr_emit);

    _compile_loop();

    _compile_pr(op_exit);
