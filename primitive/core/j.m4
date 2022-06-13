__primitive(pr_j)
{
    /* J ( -- w )

       w is a copy of the index of the next outer loop.  May only
       be used within a nested DO-LOOP or DO-+LOOP in the form, for
       example:

           DO ... DO ... J ... LOOP ... +LOOP
     */

    *--sp = *(rp+2);
}
__end
__define_primitive("J", pr_j);
