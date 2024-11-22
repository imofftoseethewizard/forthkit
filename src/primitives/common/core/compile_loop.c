pr_compile_loop:
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
