/* _store_data(0) below reserves space for the relative addr of
 * the first code cell after the end of the loop, to be filled in
 * by LOOP or +LOOP.
 */
#define _compile_do()                \
    do {                             \
        _compile_pr(op_do1);         \
        _store_data(0);              \
        *--sp = _from_ptr(dp);       \
    } while (0)

__primitive(pr_compile_do)
{
    /* DO ( w1 w2 -- ) compiling: ( -- sys )

       Used in the form:

       |   DO ... LOOP

       or

       |   DO ... +LOOP

       Begins a loop which terminates based on control parameters.
       The loop index begins at w2, and terminates based on the
       limit w1. See LOOP and +LOOP for details on how the loop is
       terminated. The loop is always executed at least once. sys
       is balanced with its corresponding LOOP or +LOOP .

       An error condition exists if insufficient space is available
       for at least three nesting levels.
     */

    _compile_do();
    _check_dictionary_bounds();
}
__end
__define_immediate_primitive("DO", pr_compile_do);
