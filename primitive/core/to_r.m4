__primitive(pr_to_r)
{
    *--rp = *sp++;
    _check_return_stack_bounds();
}
__end
__define_primitive(">R", pr_to_r);
