primitive pr_compile_begin()
{
    /* BEGIN ( -- ) compiling: ( -- sys )

       Used in the form:

       |   BEGIN ... flag UNTIL

       or

       |   BEGIN ... flag WHILE ... REPEAT

       BEGIN marks the start of a word sequence for repetitive
       execution.  A BEGIN-UNTIL loop will be repeated until flag
       is true.  A BEGIN-WHILE-REPEAT will be repeated until flag
       is false.  The words after UNTIL or REPEAT will be executed
       when either loop is finished.  sys is balanced with its
       corresponding UNTIL or WHILE .
     */

    _compile_begin();
}
