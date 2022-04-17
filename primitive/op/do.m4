/* DO et al use the top two cells of the return stack to store the loop limit and the current
   loop index, resp. op_do performs the run time activity for DO, just the copy. Implementing
   this as a primitive operation simplifies a common operation. Otherwise, this would be SWAP >R
   >R. That's the overhead of two additional _next() transitions.
*/
primitive(op_do) {
    *--rp = *(sp+1);
    *--rp = *sp;
    sp += 2;
    _next();
}

_register_operator(ot_do, op_do);
