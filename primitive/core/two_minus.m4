__primitive(pr_two_minus)
{
    /* 2- ( w1 -- w2 ) "two-minus"

       w2 is the result of subtracting two from w1 according to the
       operation of - .
     */
    *sp -= 2;
}
__end
__define_primitive("2-", pr_two_minus);
