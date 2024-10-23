__primitive(pr_bury)
{
    /* bury ( +n -- w )
           0 bury is equivalent to dup
           1 bury is equivalent to dup
           2 bury is equivalent to swap over
           x bury is equivalent to x poke drop
     */

    register number n = *sp++;
    register i;

    if (!_is_valid_0_based_stack_index(n))
        _abort(err_invalid_numeric_argument);

    for (i = 0; i <= n; i++)
        *(sp + i - 1) = *(sp + i);

    *(sp + n) = *(sp-1);
}
__end
__define_primitive("bury", pr_bury);
