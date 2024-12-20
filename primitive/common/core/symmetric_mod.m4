__primitive(pr_mod)
{
    /* mod ( n1 n2 -- n3 )

       Divide n1 by n2,  leaving the remainder n3, with the same sign
       as n1.
     */

    *++sp = (number)*(sp+1) % (number)*sp;
}
__end
__define_primitive("MOD", pr_mod);
