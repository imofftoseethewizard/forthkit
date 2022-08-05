__primitive(pr_2bury)
{
    register number n = *sp++;
    register i;

    if (!_is_valid_0_based_stack_index(2*n))
        _abort(err_invalid_numeric_argument);

    for (i = 0; i <= 2*n; i ++)
        *(sp + i - 2) = *(sp + i);

    *(sp + 2*n) = *(sp-1);
    *(sp + 2*n-1) = *(sp-2);
}
__end
__define_primitive("2bury", pr_2bury);
