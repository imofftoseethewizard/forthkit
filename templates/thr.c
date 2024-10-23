while (ip && !result) {

    _trace("main loop: ");

    if (!_is_primitive(*ip))
        _enter();

    else
        ((native_word *)(_to_pv(*ip++)))();

    _check_parameter_stack_bounds();
    _print_stack();
}
