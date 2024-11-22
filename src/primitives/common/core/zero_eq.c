/*|

`0= ( w -- flag )`

`flag` is true if `w` is zero.

  |*/

// 0=

pr_zero_eq:
{
    *sp = *sp == 0;
}
