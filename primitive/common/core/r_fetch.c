pr_r_fetch:
{
    /* R@ ( -- n ) "r-fetch"

       n is a copy of the top of the return stack.
     */

    *--sp = *rp;
}
