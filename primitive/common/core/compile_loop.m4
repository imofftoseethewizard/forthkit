/* op_loop tests the limit condition, and if met, skips over the next
   two instructions, leaving space for a jump back to the top of the loop.
*/
#define _compile_loop()                      \
    do {                                     \
        register cell *xp = _to_ptr(*sp++);  \
        _compile_pr(op_loop);                \
        _compile_pr(op_jump);                \
        _store_data((char *)xp - dp);        \
        xp--;                                \
        *xp = _from_ptr(dp);                 \
    } while (0)

__primitive(pr_compile_loop)
{
    /* LOOP

       compiling: ( addr --  )
       run-time: ( R: addr limit i -- addr limit i+1 | )

       Increments the DO-LOOP index by one. If the new index was
       incremented across the boundary between limit-1 and limit
       the loop is terminated and loop control parameters are
       discarded. When the loop is not terminated, execution
       continues to just after the corresponding DO . sys is
       balanced with its corresponding DO .
     */

    _compile_loop();
    _check_dictionary_bounds();
}
__end
__define_immediate_primitive("LOOP", pr_compile_loop);
