/*|

`< ( n1 n2 -- flag )`

`flag` is true if `n1` is less than `n2`.

  |*/

// <

pr_lt:
{
    *++sp = (number)*(sp+1) < (number)*sp;
}
