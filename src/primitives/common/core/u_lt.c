/*|

`U< ( u1 u2 -- flag )`

`flag` is true if `u1` is less than `u2`.

  |*/

// U<

pr_u_lt:
{
    *++sp = *(sp+1) < *sp;
}
