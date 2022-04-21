/* DO et al use the top two cells of the return stack to store the loop limit and the current
   loop index, resp. op_plus_loop performs the run time activity for LOOP: update index, compare
   and branch ahead 2, allowing space to compile a jump to the top of the loop.
*/
__primitive(op_plus_loop)  
{

    register number n = *(number *)sp++;

    *(number *)rp += n;

    if ((n >= 0 && *(number *)rp >= *(number *)(rp + 1))
        || (n < 0 && *(number *)rp < *(number *)(rp + 1))) {

        /* drop the loop limit and index from the return stack. */
        rp += 2;

        /* advance over the following op_jump that would return to the start of the loop. */
        ip += 2;
    }

}
__end
