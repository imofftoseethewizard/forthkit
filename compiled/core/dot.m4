
    /* . ( n -- ) "dot"

       Display  n converted according to BASE in a free field format
       with one trailing blank and with a leading minus sign if n is
       negative.

       |   : .
       |       dup 0< if 45 emit then
       |       abs u.
       |   ;
     */

    __compiled_word(".", cw_dot, 0)

    _compile_pr(pr_num_start);

    _compile_pr(pr_dup);
    _compile_pr(pr_zero_lt);
    _compile_if();
    _compile_literal('-');
    _compile_pr(pr_emit);
    _compile_then();

    _compile_pr(pr_abs);
    _compile_cw(cw_u_dot);

    _compile_pr(op_exit);
