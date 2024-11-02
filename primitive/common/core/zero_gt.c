pr_zero_gt:
{
    /* 0> ( n -- flag ) "zero-greater"

       flag is true if n is greater than zero.
     */
    *sp = (number)*sp > 0;
}
