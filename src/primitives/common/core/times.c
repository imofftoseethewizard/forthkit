/*|

`* ( n1 n2 -- n3 )`

Leave the arithmetic product of `n1` times `n2`.

  |*/

// *

pr_times:
{
    *++sp = (number)*(sp+1) * (number)*sp;
}
