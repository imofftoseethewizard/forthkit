__primitive(pr_dup)
{
    /* DUP ( n -- n n ) "dupe"

       Duplicate the value on the top of the stack.
     */

    cell n = *sp;
    *--sp = n;
}
__end
__define_primitive("DUP", pr_dup);
