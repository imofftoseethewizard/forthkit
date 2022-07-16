__primitive(pr_not_equals)
{
    _check_minimum_stack_depth(2);
    sp++;
    *sp = *sp != *(sp-1);
}
__end
__define_primitive("<>", pr_not_equals);
