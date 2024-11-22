/*|

`R@ ( -- n )`

`n` is a copy of the top of the return stack.

  |*/

// R@

pr_r_fetch:
{
    *--sp = *rp;
}
