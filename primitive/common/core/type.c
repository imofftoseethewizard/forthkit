primitive pr_type()
{
    /* TYPE ( addr n -- )

       n characters are displayed from memory beginning with the
       character at addr and continuing through consecutive
       addresses. No action takes place for n less than or equal
       to zero.
     */

    if ((number)*sp > 0)
        fwrite(_to_ptr(*(sp+1)), 1, *sp, stdout);

    sp += 2;
}
