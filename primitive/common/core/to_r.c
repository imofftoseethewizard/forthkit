pr_to_r:
{
    /* >R ( n -- ) "to-r"

       Transfer n to the return stack. Every >R must be balanced by
       a R> in the same control structure nesting level of a colon-
       definition.
     */

    *--rp = *sp++;
    _check_return_stack_bounds();
}
