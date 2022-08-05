__primitive(pr_r_fetch)
{
    /* R@ ( -- n ) "r-fetch"

       n is a copy of the top of the return stack.
     */

    *--sp = *rp;
}
__end
__define_primitive("r@", pr_r_fetch);
