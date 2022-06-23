__primitive(pr_zero_gt)
{
    /* 0> ( n -- flag ) "zero-greater"

       flag is true if n is greater than zero.
     */
    *sp = (number)*sp > 0;
}
__end
__define_primitive("0>", pr_zero_gt);
