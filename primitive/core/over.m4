__primitive(pr_over)
{
    /* OVER ( n1 n2 -- n1 n2 n1 )

       Leave a copy of the second number on the stack.
     */

    *--sp = *(sp+2);
}
__end
__define_primitive("OVER", pr_over);
