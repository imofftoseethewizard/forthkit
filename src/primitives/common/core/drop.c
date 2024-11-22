/*|

`DROP ( n -- )`

Drop the top value from the stack.

  |*/

// DROP

pr_drop:
{
    ++sp;
}
