
    /* TIB ( -- addr ) "t-i-b"

       The address of the text input buffer.  This buffer is used
       to hold characters when the input stream is coming from the
       current input device.  The minimum capacity of TIB is 80
       characters.
     */
    __compiled_word("TIB", cw_tib, c_value)
    _compile_literal(e[ea_source_addr]);
    _compile_pr(op_exit);
