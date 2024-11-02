pr_cr:
{
    /* CR ( -- ) "c-r"

       Displays a carriage-return and line-feed or equivalent
       operation.
     */

    *--sp = 10; /* ASCII line feed */
    *--sp = 13; /* ASCII carriage return */
    _emit();
    _emit();
}
