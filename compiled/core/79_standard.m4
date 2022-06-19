
    /* 79-STANDARD ( -- )

       Execute assuring that a FORTH-79 Standard system is available,
       otherwise an error condition exists.
     */

    __compiled_word("79-STANDARD", cw_79_standard, 0)
    _compile_pr(op_exit);
