primitive pr_two_divide()
{
    /* 2/ ( n1 -- n2 ) "two-divide"

       n2 is the result of arithmetically shifting n1 right one
       bit.  The sign is included in the shift and remains
       unchanged.
     */
    *sp = (number)*sp / 2 - (*sp & c_msb && *sp & 1);
}
