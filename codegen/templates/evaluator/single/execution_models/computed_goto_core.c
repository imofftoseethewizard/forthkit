#define _next()                           \
    do {                                  \
        if (!ip || result)                \
            goto __last;                  \
                                          \
        _check_parameter_stack_bounds();  \
        _print_stack();                   \
                                          \
        _trace("early main loop: ");      \
                                          \
        /*{ execute_thread_step }*/       \
    }                                     \
    while (1)

__first:

    if (0) {
	    /*{ primitive_implementations }*/

      op_enter:
        {
            _enter();
        }
        _next();
    }

    _next();

__last:
