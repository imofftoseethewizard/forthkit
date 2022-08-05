__primitive(pr_definitions)
{
    /* DEFINITIONS ( -- )

       The compilation vocabulary is changed to be the same as the
       first vocabulary in the search order.
     */

    tp[ta_current] = tp[ta_context];
}
__end
__define_primitive("definitions", pr_definitions);
