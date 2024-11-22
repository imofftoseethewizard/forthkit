/*|

`PAD ( -- addr )`

The lower address of a scratch area used to hold data for intermediate
processing.  The address or contents of `PAD` may change and the data
lost if the address of the next available dictionary location is
changed.  The minimum capacity of `PAD` is 84 characters.

  |*/

// PAD

pr_pad:
{
    *--sp = e[ea_pad];
}
