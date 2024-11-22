/*|

`0> ( n -- flag )`

`flag` is true if `n` is greater than zero.

  |*/

// 0>

pr_zero_gt:
{
    *sp = (number)*sp > 0;
}
