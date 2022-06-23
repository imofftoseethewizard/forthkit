/* op_loop tests the limit condition, and if met, skips over the next
   two instructions, leaving space for a jump back to the top of the loop.
*/
#define _compile_loop()                          \
    do {                                         \
        _compile_pr(op_loop);                    \
        _compile_pr(op_jump);                    \
        _store_data((char *)_to_ptr(*sp) - dp);  \
        _compute_leave_jumps();                  \
        sp += 2;                                 \
    } while (0)

__primitive(pr_compile_loop)
{
    _compile_loop();
    _check_dictionary_bounds();
}
__end
__define_immediate_primitive("LOOP", pr_compile_loop);
