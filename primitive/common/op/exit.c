op_exit:
{
    /* EXIT ( -- )

       When compiled within a colon-definition,  terminate  execution
       of that definition,  at that point.   May not be used within a
       DO...LOOP.

    */

    ip = *rp ? _to_ptr(*rp) : 0;

    rp++;

    if (rp >= rp_stop) steps = 0;

    _check_return_stack_bounds();
}
