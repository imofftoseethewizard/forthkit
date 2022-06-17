
    /* #S ( ud -- 0 0 ) "sharp-s"

       ud is converted appending each resultant character into the
       pictured numeric output string until the quotient (see: # )
       is zero.  A single zero is added to the output string if the
       number was initially zero. Typically used between <# and
       #> .

       |   : #S ( ud -- 0 )
       |     # begin over over or while # repeat
       |   ;
     */
    __compiled_word(`"#S"', cw_sharp_s, 0)
    _compile_pr(pr_sharp);
    _compile_begin();
    _compile_pr(pr_over);
    _compile_pr(pr_over);
    _compile_pr(pr_or);
    _compile_while();
    _compile_pr(pr_sharp);
    _compile_repeat();
    _compile_pr(op_exit);
