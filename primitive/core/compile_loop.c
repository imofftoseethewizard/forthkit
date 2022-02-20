/* op_loop tests the limit condition, and if met, skips over the next
   two instructions, leaving space for a jump back to the top of the loop.
*/
#define _compile_loop()                                             \
    do {                                                            \
        _compile_pr(op_loop);                                       \
        _compile_pr(op_jump);                                       \
        _store_data((char *)_to_ptr(*sp++) - here + sizeof(cell));  \
    } while (0)

_primitive(pr_compile_loop) {

    _compile_loop();
    _next();
}
_define_immediate_primitive("LOOP", pr_compile_loop);
