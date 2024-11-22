/*|

`R> ( -- n )`

Transfer `n` from the return stack to the data stack.

  |*/

// R>

pr_r_from:
{
    *--sp = *rp++;
    _check_return_stack_bounds();
}
