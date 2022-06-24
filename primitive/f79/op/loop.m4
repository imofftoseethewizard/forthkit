/* DO et al use the top two cells of the return stack to store the loop limit and the current
   loop index, resp. op_loop performs the run time activity for LOOP: increment, compare and
   branch ahead 2, allowing space to compile a jump to the top of the loop.
*/
__primitive(op_loop)
{

    (*rp)++;

    if (*(number *)rp < *(number *)(rp + 1))
        ip = (cell *)((char *)ip + (number)*ip);

    else {

        /* drop the loop limit and index from the return stack. */
        rp += 2;

        /* advance over the address of the start of the loop.
         */
        ip++;

        _check_return_stack_bounds();
    }
}
__end

__define_primitive("<loop>", op_loop);
