/*|

`PICK ( n1 -- n2 )`

Return the contents of the `n1`th stack value, not counting `n1`
itself.  An error condition results for `n` less than one.

2 PICK is equivalent to OVER.

  |*/

// PICK

pr_pick:
{
    register number n = *sp++;

    if (!_is_valid_1_based_stack_index(n))
        _abort(err_invalid_numeric_argument);

    else
        *--sp = *(sp + n - 1);
}
