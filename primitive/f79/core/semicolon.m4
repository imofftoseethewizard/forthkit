__primitive(pr_semicolon)
{
    /* ; ( -- ) "semi-colon"
         compiling: ( sys -- )

         Stops compilation of a colon definition, allows the <name>
         of this colon definition to be found in the dictionary, sets
         interpret state and compiles EXIT (or a system dependent
         word which performs an equivalent function).  sys is
         balanced with its corresponding : .
     */

    _compile_pr(op_exit);
    tp[ta_state] = 0;

    _check_dictionary_bounds();
}
__end
__define_immediate_primitive(";", pr_semicolon);
