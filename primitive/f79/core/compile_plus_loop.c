primitive pr_compile_plus_loop()
{
    /* +LOOP ( n -- ) "plus-loop"
             compiling: ( sys -- )

       n is added to the loop index.  If the new index was
       incremented across the boundary between limit-1 and limit
       then the loop is terminated and loop control parameters are
       discarded.  When the loop is not terminated, execution
       continues to just after the corresponding DO .  sys is
       balanced with its corresponding DO .  See:  DO
     */

    _compile_pr(op_plus_loop);
    _store_data((char *)_to_ptr(*sp++) - dp);

    _check_dictionary_bounds();
}
