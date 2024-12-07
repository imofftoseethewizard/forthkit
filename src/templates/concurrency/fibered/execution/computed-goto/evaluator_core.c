#define _next()                           \
    do {                                  \
        if (!ip || !steps || result )     \
            goto op_end_fiber;            \
                                          \
        _check_parameter_stack_bounds();  \
        _print_stack();                   \
                                          \
        if (steps > 0) steps -= 1;        \
                                          \
        /*{ thread_step }*/               \
    }                                     \
    while (1)

    /*{ prepare_evaluation }*/

__first:

    if (0) {
        /*{ primitive_implementations }*/

      op_end_fiber:
        {
            if (fp < fp0) {
                _debug("saving fiber %d\n", *fp);
                _print_registers();

                _save_fiber_state();
                fp++;
            }

            if (fp == fp0 || result)
                goto __last;

            _print_fiber_stack();
            _load_fiber_state();
        }
        _next();
    }

    _next();

__last:
