__primitive(pr_u_lt)
{
    /* U< ( u1 u2 -- flag ) "u-less-than"

       flag is true if u1 is less than u2.
     */

    *++sp = *(sp+1) < *sp;
}
__end
__define_primitive("U<", pr_u_lt);
