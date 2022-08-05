__primitive(pr_2dup)
{
    _check_minimum_stack_depth(2);
    sp -= 2;
    *(sp+1) = *(sp+3);
    *sp = *(sp+2);
}
__end
__define_primitive("2dup", pr_2dup);
