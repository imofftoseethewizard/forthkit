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

      op_enter:
        {
            _enter();
        }
        _next();
    }

    _next();

__last:
