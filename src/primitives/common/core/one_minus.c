/*|

`1- ( w1 -- w2 )`

`w2` is the result of subtracting one from `w1` according to the
operation of `-`.

  |*/

// 1-

pr_one_minus:
{
    *sp -= 1;
}
