
    /* SPAN ( -- addr )

       The address of a variable containing the count of characters
       actually received and stored by the last execution of
       EXPECT .
     */
    __compiled_word("SPAN", cw_span, c_value)
    _compile_variable();
