_compiled_word(":", 0) {
    /*
       : :
         current @ context ! create ]
       ;

     */
    _compile_pr(pr_current);
    _compile_pr(pr_fetch);
    _compile_pr(pr_context);
    _compile_pr(pr_store);
    _compile_pr(op_literal);
    _store_data(32);
    _compile_pr(pr_word);
    _compile_pr(pr_do_create);
    _compile_pr(pr_right_bracket);
    _compile_pr(op_exit);
}
