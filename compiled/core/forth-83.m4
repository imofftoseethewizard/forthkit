
    /* FORTH-83 ( -- )

       Execute assuring that a FORTH-83 Standard system is available,
       otherwise an error condition exists.
     */

    __compiled_word("FORTH-83", cw_forth_83, 0)
    _compile_pr(op_exit);
