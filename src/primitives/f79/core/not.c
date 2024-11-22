/*|

`NOT ( flag1 -- flag2 )`

Reverse the boolean value of `flag1`.  This is identical to `0=`.

  |*/

// NOT

pr_not:
{
    *sp = *sp == 0;
}
