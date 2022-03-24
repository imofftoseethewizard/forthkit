/* op_loop tests the limit condition, and if met, skips over the next
   two instructions, leaving space for a jump back to the top of the loop.
*/
#define _compile_loop()                                             \
    do {                                                            \
        _compile_pr(op_loop);                                       \
        _compile_pr(op_jump);                                       \
        _store_data((char *)_to_ptr(*sp++) - here + sizeof(cell));  \
    } while (0)
