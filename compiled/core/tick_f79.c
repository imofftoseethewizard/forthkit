_compiled_word("'", c_immediate) {
    /*
       : '
         32 word find ?dup if
             state @ if literal then
         else
             abort
         then
       ; immediate
     */

    _compile_pr(op_literal);
    _store_data(32);
    _compile_pr(pr_word);
    _compile_pr(pr_find);
    _compile_pr(pr_q_dup);
    _compile_if();
    _compile_pr(pr_state);
    _compile_pr(pr_fetch);
    _compile_if();
    _compile_pr(pr_literal);
    _compile_then();
    _compile_else();
    _compile_pr(pr_abort);
    _compile_then();
    _compile_pr(op_exit);
}
