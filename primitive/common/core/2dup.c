pr_2dup:
{
    _check_minimum_stack_depth(2);
    sp -= 2;
    *(sp+1) = *(sp+3);
    *sp = *(sp+2);
}
