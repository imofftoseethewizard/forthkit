/* op_loop tests the limit condition, and if met, skips over the next
   two instructions, leaving space for a jump back to the top of the loop.
*/
#define _compile_loop()                      \
    do {                                     \
        register cell *xp = _to_ptr(*sp++);  \
        _compile_pw(op_loop);                \
        _store_data((char *)xp - dp);        \
        xp--;                                \
        *xp = _from_ptr(dp);                 \
    } while (0)
