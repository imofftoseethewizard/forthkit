__primitive(pr_sign)
{
    /* SIGN ( n -- )

       If n is negative, an ASCII "-" (minus sign) is appended to
       the pictured numeric output string.  Typically used between
       <# and #> .
    */

    if (*(number *)sp++ < 0)
        _hold('-');
}
__end
__define_primitive("SIGN", pr_sign);
