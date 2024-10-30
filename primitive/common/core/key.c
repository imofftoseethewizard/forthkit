primitive pr_key()
{
    /* KEY ( -- char )

       Leave the ASCII value of the next available character from the
       current input device. Characters received by KEY will not be
       displayed.
     */

    *--sp = getc(stdin);
}
