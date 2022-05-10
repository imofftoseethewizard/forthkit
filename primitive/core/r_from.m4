__primitive(pr_r_from)
{
    *--sp = *rp++;
    _check_return_stack_bounds();
}
__end
__define_primitive("R>", pr_r_from);
