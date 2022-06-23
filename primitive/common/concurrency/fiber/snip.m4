__primitive(pr_snip)
{
    *(fp+1) = *fp;
    fp++;
    _check_fiber_stack_bounds();
}
__end

__define_primitive("snip", pr_snip);
