primitive op_plus_loop()
{
    /* <+loop> "op-plus-loop"

       DO et al use the top three cells of the return stack to
       store the leave target address, loop limit, and the current
       loop index, resp. op_plus_loop performs the run time
       activity for +LOOP: update index, compare and branch ahead
       2, allowing space to compile a jump to the top of the loop.
     */

    register cell
      i0 = *rp,
      limit = *(rp + 1),
      step = *sp++,
      k = (*rp = i0 + step) - limit;

    /* The first term will have msb true if i0 is on the other
       side of limit from i0 + step. The second term will have msb
       true when step and i0 + step are on the same side of limit.
     */

    if ((~(k ^ (i0 - limit)) | (k ^ step)) & c_msb)
        ip = (cell *)((char *)ip + (number)*ip);

    else {

        /* drop the leave target address, loop limit, and index from
           the return stack.
         */
        rp += 3;

        /* advance over the address of the start of the loop.
         */
        ip++;
    }
}
