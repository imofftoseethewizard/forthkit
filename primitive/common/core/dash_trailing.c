primitive pr_dash_trailing()
{
    /* -TRAILING ( addr u1 -- addr u2 ) "dash-trailing"

       The character count u1 of a text string beginning at addr
       is adjusted to exclude trailing spaces. If u1 is zero,
       then u2 is also zero. If the entire string consists of
       spaces, then u2 is zero.

     */

    register number n = (number)*sp;
    register char *s = (char *)_to_ptr(*(sp+1));

    while (n > 0 && s[n-1] == 32)
        n--;

    *sp = n;
}
