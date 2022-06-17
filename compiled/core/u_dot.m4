
    /* u. ( u -- ) "u-dot"

       Display u converted according to BASE in a free field format
       with one trailing blank.

       |   : .
       |       0 <# #s #> type
       |       32 emit
       |   ;
     */

    __compiled_word("U.", cw_u_dot, 0)

    _compile_pr(pr_num_start);

    _compile_literal(0);
    _compile_pr(pr_num_start);
    _compile_cw(cw_sharp_s);
    _compile_pr(pr_num_end);
    _compile_pr(pr_type);

    _compile_literal(' ');
    _compile_pr(pr_emit);

    _compile_pr(op_exit);
