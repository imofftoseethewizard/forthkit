__primitive(pr_and)
{
    /* AND ( n1 n2 -- n3 )

     Leave the bitwise logical 'and' of n1 and n2.
     */

    *++sp = *(sp+1) & *sp;
}
__end
__define_primitive("AND", pr_and);
