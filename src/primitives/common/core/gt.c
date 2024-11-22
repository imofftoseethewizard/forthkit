/*|

`> ( n1 n2 -- flag )`

`flag` is true if `n1` is greater than `n2`.

  |*/

// >

pr_gt:
{
    *++sp = (number)*(sp+1) > (number)*sp;
}
