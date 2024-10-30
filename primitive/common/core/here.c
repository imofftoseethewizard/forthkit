primitive pr_here()
{
    /* HERE ( -- addr )

       The address of the next available dictionary location.
     */

    *--sp = _from_ptr(dp);
}
