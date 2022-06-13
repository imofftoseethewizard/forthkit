__primitive(pr_min)
{
    /* MIN ( n1 n2 -- n3 ) "min"

       n3 is the lesser of n1 and n2 according to the operation of
       < .
     */

    *++sp = (number)*(sp+1) > (number)*sp ? *sp : *(sp+1);
}
__end
__define_primitive("MIN", pr_min);
