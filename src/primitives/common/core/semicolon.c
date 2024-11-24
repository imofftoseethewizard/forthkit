pr_semicolon:
{
    /* ; ( -- ) "semi-colon"
         compiling: ( sys -- )

         Stops compilation of a colon definition, allows the <name>
         of this colon definition to be found in the dictionary, sets
         interpret state and compiles EXIT (or a system dependent
         word which performs an equivalent function).  sys is
         balanced with its corresponding : .
     */

    _compile_pw(op_exit);
    _set_state(0);

    _end_define_word();

    _check_dictionary_bounds();
}
