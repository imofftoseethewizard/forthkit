__primitive(pr_not)
{
    /* NOT ( w1 -- w2 )

       w2 is the one's complement of w1.
    */

    *sp = ~*sp;
}
__end
__define_primitive("not", pr_not);
