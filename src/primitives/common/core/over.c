/*|

`OVER ( n1 n2 -- n1 n2 n1 )`

Leave a copy of the secon`d number on the stack.

  |*/

// OVER

pr_over:
{
    register cell n = *(sp+1);
    *--sp = n;
}
