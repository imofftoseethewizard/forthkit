primitive pr_lay()
{
    register cell idx = *sp++;

    if (_is_fiber_stack_full())
        _abort(err_fiber_stack_overflow);

    else if (!_is_valid_fiber_number(idx))
        _abort(err_invalid_fiber_number);

    else if (_is_active_fiber_number(idx))
        _abort(err_active_fiber_not_allowed);

    else {
        register cell f = *fp;
        *fp = idx;
        *--fp = f;
    }
}
