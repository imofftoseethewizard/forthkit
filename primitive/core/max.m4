__primitive(pr_max)
{
    /* MAX ( n1 n2 -- n3 ) "max"

       n3 is the greater of n1 and n2 according to the operation of
       > .
     */

    *++sp = (number)*(sp+1) < (number)*sp ? *sp : *(sp+1);
}
__end
__define_primitive("MAX", pr_max);
