    /*{ primitive_implementations }*/

	while (ip && !result) {

		_trace("early main loop: ");

		/*{ thread_step }*/

		_check_parameter_stack_bounds();
		_print_stack();
	}