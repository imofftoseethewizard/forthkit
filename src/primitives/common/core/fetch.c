/*|

`@ ( addr -- n )`

Leave on the stack the number contained at `addr`.

  |*/

// @

pr_fetch:
{
    *sp = *_to_ptr(*sp);
}
