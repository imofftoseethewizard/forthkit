__primitive(pr_roll)
{
    /* ROLL ( +n -- )

       The +nth stack value, not counting +n itself is first
       removed and then transferred to the top of the stack, moving
       the remaining values into the vacated position.  {0..the
       number of elements on the stack-1}

           2 ROLL is equivalent to ROT
           0 ROLL is a null operation
     */

    register number n = *sp++;

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
__end
__define_primitive("roll", pr_roll);
