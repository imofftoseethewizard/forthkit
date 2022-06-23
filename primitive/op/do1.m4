__primitive(op_do1)
{
    /* DO et al use the top two cells of the return stack to store
       the loop limit and the current loop index, resp. op_do0 and
       op_do1 performs the run time activity for DO, ie just the
       copy. In addition, op_do1 skips the next cell, which is
       reserved to hold the relative address of the first code
       cell after the end of the loop.
     */


    /* skip over the address of the first cell after the loop,
       storing it on the return stack for use by leave.
     */

    *--rp = *ip++;
    *--rp = *(sp+1);
    *--rp = *sp;
    sp += 2;

    _check_return_stack_bounds();
}
__end

__define_primitive("<do>", op_do1);
