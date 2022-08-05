__primitive(pr_u_gt)
{
    /* U< ( u1 u2 -- flag ) "u-greater-than"

       flag is true if u1 is greater than u2.
     */

    *++sp = *(sp+1) > *sp;
}
__end
__define_primitive("u>", pr_u_gt);
