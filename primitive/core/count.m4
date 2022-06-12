__primitive(pr_count)
{
    /* COUNT ( addr -- addr+1 n )

       Leave  the  address  addr+1 and the character  count  of  text
       beginning  at addr.   The first byte at addr must contain  the
       character count n.  Range of n is {0..255}.
     */

    register length_type *lenp = (length_type *)_to_ptr(*sp);

    *sp = _from_ptr(lenp + 1);
    *--sp = *lenp;
}
__end
__define_primitive("COUNT", pr_count);
