__primitive(pr_one_plus)
{
    /* 1+ ( w1 -- w2 ) "one-plus"

       w2 is the result of adding one to w1 according to the
       operations of + .
     */
    *sp += 1;
}
__end
__define_primitive("1+", pr_one_plus);
