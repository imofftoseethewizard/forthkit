/*|

`2- ( w1 -- w2 )`

`w2` is the result of subtracting two from `w1` according to the
operation of `-`.

  |*/

// 2-

pr_two_minus:
{
    *sp -= 2;
}
