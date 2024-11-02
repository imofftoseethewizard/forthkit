pr_zero_eq:
{
    /* 0= ( w -- flag ) "zero-equals"

       flag is true if w is zero.
     */
    *sp = *sp == 0;
}
