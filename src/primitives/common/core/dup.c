/*|

`DUP ( n -- n n )`

Duplicate the value on the top of the stack.

  |*/

// DUP

pr_dup:
{
    cell n = *sp;
    *--sp = n;
}
