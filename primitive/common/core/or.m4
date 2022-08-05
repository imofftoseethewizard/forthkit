__primitive(pr_or)
{
    /* OR ( n1 n2 -- n3 )

       Leave the bitwise inclusive-or of two numbers.
     */

    *++sp = *(sp+1) | *sp;
}
__end
__define_primitive("or", pr_or);
