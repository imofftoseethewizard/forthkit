primitive pr_two_plus()
{
    /* 2+ ( w1 -- w2 ) "two-plus"
       w2 is the result of adding two to w1 according to the
       operation of + .

     */
    *sp += 2;
}
