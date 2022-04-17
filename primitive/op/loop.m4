/* DO et al use the top two cells of the return stack to store the loop limit and the current
   loop index, resp. op_loop performs the run time activity for LOOP: increment, compare and
   branch ahead 2, allowing space to compile a jump to the top of the loop.
*/
primitive(op_loop) {

    (*rp)++;

    if (*(number *)rp >= *(number *)(rp + 1)) {
        /* drop the loop limit and index from the return stack. */
        rp += 2;

        /* advance over the following op_jump that would return to the start of the loop. */
        ip += 2;
    }

    _next();
}

_register_operator(ot_loop, op_loop);
