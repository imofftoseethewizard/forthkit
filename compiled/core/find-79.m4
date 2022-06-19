
    /* FIND ( -- addr )

       Leave the compilation address of the next word name, which is
       accepted from the input stream. If that word cannot be found
       in the dictionary after a search of CONTEXT and FORTH leave
       zero.

       |   : find
       |       32 word find 0=
       |       if
       |           drop
       |           0
       |       then
       |   ;
    */

    __compiled_word("FIND", cw_find, 0)

    _compile_literal(32);
    _compile_cw(cw_word);
    _compile_pr(pr_find);
    _compile_pr(pr_zero_eq);

    _compile_if();

    _compile_pr(pr_drop);
    _compile_literal(0);

    _compile_then();

    _compile_pr(op_exit);
