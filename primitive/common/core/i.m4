__primitive(pr_i)
{
    /* I ( -- w )

       w is a copy of the loop index.  May only be used in the
       form:

           DO ... I ... LOOP

       or

           DO ... I ... +LOOP
     */

    *--sp = *rp;
}
__end
__define_primitive("i", pr_i);
