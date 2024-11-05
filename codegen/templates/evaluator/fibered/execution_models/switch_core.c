    while (fp < fp0 && !result) {

        _print_fiber_stack();
        _load_fiber_state();

        _debug("loaded fiber %d\n", *fp);
        _print_registers();

        while (ip && steps && !result) {

            if (steps > 0) steps -= 1;

            _trace("early main loop: ");

            /*{ execute_thread_step }*/

            _check_parameter_stack_bounds();
            _print_stack();
       }

        if (fp < fp0) {
            _debug("saving fiber %d\n", *fp);
            _print_registers();

            _save_fiber_state();
            fp++;
        }
    }
