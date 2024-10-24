__primitive(pr_forth)
{
    /* FORTH ( -- )

       The name of the primary vocabulary. Execution replaces the
       first vocabulary in the search order with FORTH . FORTH is
       initially the compilation vocabulary and the first
       vocabulary in the search order. New definitions become part
       of the FORTH vocabulary until a different compilation
       vocabulary is established.
     */

    tp[ta_context] = _from_ptr(&tp[ta_forth]);
}
__end
__define_primitive("FORTH", pr_forth);
