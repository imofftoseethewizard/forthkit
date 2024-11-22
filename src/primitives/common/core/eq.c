/*|

`= ( w1 w2 -- flag )`

`flag` is true if `w1` is equal to `w2`.

  |*/

// =

pr_eq:
{
    register cell flag = *(sp+1) == *sp;
    *(sp+1) = flag;
    sp++;
}
