while (fp < fp0) {

    _print_fiber_stack();
    _load_fiber_state();

    _debug("loaded fiber %d\n", *fp);
    _print_registers();

    while (ip && steps && !result) {

        if (steps > 0) steps -= 1;

        _trace("main loop: ");

        if (!_is_primitive(*ip))
            _enter();

        else
            ((native_word *)(_to_pv(*ip++)))();

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
