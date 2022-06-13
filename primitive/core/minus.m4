__primitive(pr_minus)
{
    /* - ( n1 n2 -- n3 ) "minus"

       Subtract n2 from n1 and leave the difference n3.
     */
    *++sp = *(sp+1) - *sp;
}
__end
__define_primitive("-", pr_minus);
