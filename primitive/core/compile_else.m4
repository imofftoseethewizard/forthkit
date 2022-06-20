#define _compile_else()                                                 \
do {                                                                    \
    /* Jump from here -- the end of the consequent -- to the end of the \
       conditional.                                                     \
    */                                                                  \
    _compile_jump_origin();                                             \
                                                                        \
    /* Bring the origin of the branch target to the top of the stack    \
       and point it here, at the begining of the alternate.             \
    */                                                                  \
    _swap();                                                            \
    _compile_jump_target();                                             \
} while (0)

__primitive(pr_compile_else)
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
__end
__define_immediate_primitive("ELSE", pr_compile_else);
