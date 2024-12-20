/*|

`ROLL ( n -- )`

Extract the `n`th stack value to the top of the stack, not counting `n`
itself, moving the remaining values into the vacated position.  An
error condition results for `n` less than one.  `3 ROLL` is the same
as `ROT`, and `1 ROLL` has no effect.

  |*/

// ROLL

pr_roll:
{
    register number n = *sp++ - 1;

    if (!n)
        ;

    else if (!_is_valid_0_based_stack_index(n))
        _abort(err_invalid_numeric_argument);

    else {
        register cell tmp = *(sp+n);
        register cell *src = sp + n - 1;
        register cell *dest = sp + n;

        for (; n > 0; n--)
            *dest-- = *src--;

        *sp = tmp;
    }
}
