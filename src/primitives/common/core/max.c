/*|

`MAX ( n1 n2 -- n3 )`

`n3` is the greater of `n1` and `n2` according to the operation of `>`.

  |*/

// MAX

pr_max:
{
    *++sp = (number)*(sp+1) < (number)*sp ? *sp : *(sp+1);
}
