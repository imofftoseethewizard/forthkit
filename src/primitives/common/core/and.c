/*|

`AND ( n1 n2 -- n3 )`

Leave the bitwise logical 'and' of n1 and n2.

  |*/

// AND

pr_and:
{
    *++sp = *(sp+1) & *sp;
}
