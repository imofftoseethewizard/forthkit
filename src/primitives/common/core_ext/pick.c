pr_pick:
{
    /* PICK ( +n -- w )

       w is a copy of the +nth stack value, not counting +n
       itself.  {0..the number of elements on stack-1}

           0 PICK is equivalent to DUP
           1 PICK is equivalent to OVER
     */

    register number n = *sp++;

    if (!_is_valid_0_based_stack_index(n))
        _abort(err_invalid_numeric_argument);

    else
        *--sp = *(sp + n);
}
