/*|

`1+ ( w1 -- w2 )`

`w2` is the result of adding one to `w1` according to the operations
of `+`.

  |*/

// 1+

pr_one_plus:
{
    *sp += 1;
}
