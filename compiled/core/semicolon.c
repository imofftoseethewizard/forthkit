_compiled_word(";", c_immediate) {
    /*
       : :
         current @ context ! create ]
       ;

     */
    _compile_pr(pr_left_bracket);
    _compile_pr(op_exit);
}
