/*|

`CR ( -- )`

Displays a carriage-return and line-feed or equivalent operation.

  |*/

// CR

pr_cr:
{
    *--sp = 10; /* ASCII line feed */
    *--sp = 13; /* ASCII carriage return */
    _emit();
    _emit();
}
