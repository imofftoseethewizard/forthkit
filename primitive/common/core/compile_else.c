pr_compile_else:
{
    /* ELSE ( -- ) compiling: ( sys1 -- sys2 )

       Used in the form:

       |   flag IF ... ELSE ... THEN

       ELSE executes after the true part following IF . ELSE
       forces execution to continue at just after THEN . sys1 is
       balanced with its corresponding IF . sys2 is balanced with
       its corresponding THEN .
     */

    _compile_else();
}
