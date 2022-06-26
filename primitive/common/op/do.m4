__primitive(op_do)
{
    /* DO et al use the top two cells of the return stack to store
       the loop limit and the current loop index, resp. op_do and
       op_do performs the run time activity for DO, ie just the
       copy. In addition, op_do skips the next cell, which is
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

__define_primitive_ext("<do>", op_do, c_operand_ip_absolute);
