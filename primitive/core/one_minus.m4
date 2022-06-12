__primitive(pr_one_minus)
{
    /* 1- ( w1 -- w2 ) "one-minus"

       w2 is the result of subtracting one from w1 according to the
       operation of - .
     */
    *sp -= 1;
}
__end
__define_primitive("1-", pr_one_minus);
