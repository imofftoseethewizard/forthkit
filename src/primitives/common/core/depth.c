/*|

`DEPTH ( -- n )`

Leave the number of the quantity of cell values contained in the data
stack, before `n` added.

  |*/

// DEPTH

pr_depth:
{
    *--sp = sp0 - sp;
}
