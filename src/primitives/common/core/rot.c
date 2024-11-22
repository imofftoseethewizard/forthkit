/*|

`ROT ( n1 n2 n3 -- n2 n3 n1 )`

Rotate the top three values, bringing the deepest to the top.

  |*/

// ROT

pr_rot:
{
    register cell tmp = *sp;
    *sp = *(sp+2), *(sp+2) = *(sp+1), *(sp+1) = tmp;
}
