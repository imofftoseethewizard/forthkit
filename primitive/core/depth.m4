__primitive(pr_depth)
{
    /* DEPTH ( -- n )

       Leave the number of the quantity of 16-bit values contained in
       the data stack, before n added.
     */

    *--sp = sp0 - sp;
}
__end
__define_primitive("DEPTH", pr_depth);
