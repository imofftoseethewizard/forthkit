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
        /*{ thread_step }*/       \
    }                                     \
    while (1)

    /*{ prepare_evaluation }*/

__first:

    if (0) {
        /*{ primitive_implementations }*/
    }

    _next();

__last:

    _save_evaluator_state();
