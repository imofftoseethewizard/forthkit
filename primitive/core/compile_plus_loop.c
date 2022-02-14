_primitive(pr_compile_plus_loop) {

    /* op_plus_loop tests the limit condition, and if met, skips over the next
       two instructions, leaving space for a jump back to the top of the loop.
    */

    _compile_pr(op_plus_loop);

    _compile_pr(op_jump);
    _store_data((char *)_to_ptr(*sp++) - here + sizeof(cell));

    _next();
}
_define_immediate_primitive("+LOOP", pr_compile_plus_loop);
