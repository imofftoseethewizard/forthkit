/*|

`2+ ( w1 -- w2 )`

`w2` is the result of adding two to `w1` according to the operation of
`+`.

  |*/

// 2+

pr_two_plus:
{
    *sp += 2;
}
