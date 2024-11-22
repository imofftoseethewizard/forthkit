/*|

`- ( n1 n2 -- n3 )`

Subtract `n2` from `n1` and leave the difference `n3`.

  |*/

// -

pr_minus:
{
    *++sp = *(sp+1) - *sp;
}
