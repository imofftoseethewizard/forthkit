/*|

`OR ( n1 n2 -- n3 )`

Leave the bitwise inclusive-or of two numbers.

  |*/

// OR

pr_or:
{
    *++sp = *(sp+1) | *sp;
}
