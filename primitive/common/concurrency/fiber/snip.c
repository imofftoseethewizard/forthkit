primitive pr_snip()
{
    *(fp+1) = *fp;
    fp++;
    _check_fiber_stack_bounds();
}
