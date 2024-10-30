primitive pr_dup()
{
    /* DUP ( n -- n n ) "dupe"

       Duplicate the value on the top of the stack.
     */

    cell n = *sp;
    *--sp = n;
}
