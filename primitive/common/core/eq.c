primitive pr_eq()
{
    /* = ( w1 w2 -- flag ) "equals"

       flag is true if w1 is equal to w2.
     */
    register cell flag = *(sp+1) == *sp;
    *(sp+1) = flag;
    sp++;
}
