__primitive(pr_eq)
{
    /* = ( w1 w2 -- flag ) "equals"

       flag is true if w1 is equal to w2.
     */
    *(sp+1) = *(sp+1) == *sp, sp++;
}
__end
__define_primitive("=", pr_eq);
