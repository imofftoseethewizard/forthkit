__primitive(pr_negate)
{
    /* NEGATE ( n1 -- n2 )

       n2 is the two's complement of n1, i.e, the difference of
       zero less n1.
     */

    *sp = -(number)*sp;
}
__end
__define_primitive("NEGATE", pr_negate);
