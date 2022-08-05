__primitive(pr_decimal)
{
    /* DECIMAL ( -- )

       Set the input-output numeric conversion base to ten.
     */

    tp[ta_base] = 10;
}
__end
__define_primitive("decimal", pr_decimal);
