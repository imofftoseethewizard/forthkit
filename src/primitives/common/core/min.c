/*|

`MIN ( n1 n2 -- n3 )`

`n3` is the lesser of `n1` and `n2` according to the operation of `<`.

  |*/

// MIN

pr_min:
{
    *++sp = (number)*(sp+1) > (number)*sp ? *sp : *(sp+1);
}
