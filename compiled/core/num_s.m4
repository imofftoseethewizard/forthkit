    __compiled_word(`"#S"', cw_num_s, 0)
    /*
   : #S ( ud -- 0 )
     # begin over over or while # repeat drop drop
   ;
 */
    _compile_pr(pr_sharp);
    _compile_begin();
    _compile_pr(pr_over);
    _compile_pr(pr_over);
    _compile_pr(pr_or);
    _compile_while();
    _compile_pr(pr_sharp);
    _compile_repeat();
    _compile_pr(op_exit);
