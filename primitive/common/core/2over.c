primitive pr_2over()
{
    /* 2OVER ( x1 x2 x3 x4 -- x1 x2 x3 x4 x1 x2 )

       Copy cell pair x1 x2 to the top of the stack.
     */
    _check_minimum_stack_depth(4);

    register cell *p = sp;
    *--sp = *(p+3);
    *--sp = *(p+2);
}
