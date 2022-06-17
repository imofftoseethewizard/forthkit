
    /* #TIB ( -- addr ) "number-t-i-b"

       The address of a variable containing the number of bytes in
       the text input buffer.  #TIB is accessed by WORD when BLK is
       zero.  {{0..capacity of TIB}}  See:  "input stream"
     */

    __compiled_word(`"#TIB"', cw_number_t_i_b, 0)
    _compile_literal(_from_ptr(&e[ea_source_len]));

    _compile_pr(op_exit);
