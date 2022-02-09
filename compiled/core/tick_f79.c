_compiled_word("'", c_immediate) {
    /*
       : '
         32 word find 0= if drop 0 then
       ; immediate
     */

    _compile_pr(op_literal);
    _store_data(32);
    _compile_pr(pr_find);
    _compile_pr(pr_zero_eq);
    _compile_if();
    _compile_pr(pr_drop);
    _compile_pr(op_literal);
    _store_data(0);
    _compile_then();
    _compile_pr(op_exit);
}
