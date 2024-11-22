/*|

`0< ( n -- flag )`

`flag` is true if `n` is less than zero (negative).

  |*/

// 0<

pr_zero_lt:
{
    *sp = (number)*sp < 0;
}
