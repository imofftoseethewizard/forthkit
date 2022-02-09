_compiled_word("#S", 0) {
    /*
       : #S ( ud -- 0 )
         # begin ?dup while # repeat
       ;
     */
    _compile_pr(pr_num);
    _compile_begin();
    _compile_pr(pr_q_dup);
    _compile_while();
    _compile_pr(pr_num);
    _compile_repeat();
    _compile_pr(op_exit);
}
