primitive pr_over()
{
    /* OVER ( n1 n2 -- n1 n2 n1 )

       Leave a copy of the second number on the stack.
     */

    register cell n = *(sp+1);
    *--sp = n;
}
