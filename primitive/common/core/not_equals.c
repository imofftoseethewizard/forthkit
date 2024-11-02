pr_not_equals:
{
    _check_minimum_stack_depth(2);
    sp++;
    *sp = *sp != *(sp-1);
}
