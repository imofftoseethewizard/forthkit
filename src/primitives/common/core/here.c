/*|

`HERE ( -- addr )`

The address of the next available dictionary location.

  |*/

// HERE

pr_here:
{
    *--sp = _from_ptr(dp);
}
