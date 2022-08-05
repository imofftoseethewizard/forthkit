#define _compile_if()             \
    do {                          \
        _compile_pr(op_0branch);  \
        *--sp = _from_ptr(dp);    \
        _store_data(0);           \
    } while (0)

__primitive(pr_compile_if)
{
    /* IF ( flag -- ) compiling ( -- sys )

       Used in the form:

       |   flag IF ... ELSE ... THEN

       or

       |   flag IF ... THEN

       If flag is true, the words following IF are executed and the
       words following ELSE until just after THEN are skipped.  The
       ELSE part is optional.

       If flag is false, the words from IF through ELSE , or from
       IF through THEN (when no ELSE is used), are skipped.  sys is
       balanced with its corresponding ELSE or THEN .
     */

    _compile_if();
    _check_dictionary_bounds();
}
__end
__define_immediate_primitive("if", pr_compile_if);
