primitive pr_base()
{
    /* BASE ( -- addr )

       The address of a variable containing the current numeric
       conversion radix. FORTH-79: {{2..70}}, FORTH-83: {{2..72}},
       FORTH-94 and later: {{2..36}}. Range not checked.
     */

    *--sp = _from_ptr(&tp[ta_base]);
}
