__primitive(pr_poke)
{
    /* POKE ( +n -- w )
           0 POKE is equivalent to DUP
           1 POKE is equivalent to TUCK
     */

    register number n = *sp++;
    register i;

    if (!_is_valid_0_based_stack_index(n))
        _abort(err_invalid_numeric_argument);

    for (i = 0; i <= n; i++)
        *(sp + i - 1) = *(sp + i);

    *(sp + n) = *(sp-1);

    sp--;
}
__end
__define_primitive("poke", pr_poke);
