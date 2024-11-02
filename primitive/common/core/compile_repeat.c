pr_compile_repeat:
{
    /* REPEAT compiling: ( sys -- )

       Used in the form:

       |   BEGIN ... flag WHILE ... REPEAT

       At execution time, REPEAT continues execution to just after
       the corresponding BEGIN . sys is balanced with its
       corresponding WHILE .
     */

    _compile_repeat();
    _check_dictionary_bounds();
}
