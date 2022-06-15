__primitive(pr_type)
{
    /* TYPE ( addr n -- )

       n characters are displayed from memory beginning with the
       character at addr and continuing through consecutive
       addresses. No action takes place for n less than or equal
       to zero.
     */

    if ((number)*sp > 0)
        fwrite(_to_ptr(*(sp+1)), sizeof(char), *sp, stdout);

    sp += 2;
}
__end
__define_primitive("TYPE", pr_type);
