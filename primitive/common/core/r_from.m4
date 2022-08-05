__primitive(pr_r_from)
{
    /* R> ( -- n ) "r-from"

       Transfer n from the return stack to the data stack.
     */

    *--sp = *rp++;
    _check_return_stack_bounds();
}
__end
__define_primitive("r>", pr_r_from);
