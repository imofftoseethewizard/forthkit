__primitive(pr_zero_eq)
{
    /* 0= ( w -- flag ) "zero-equals"

       flag is true if w is zero.
     */
    *sp = *sp == 0;
}
__end
__define_primitive("0=", pr_zero_eq);
