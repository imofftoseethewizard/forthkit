__primitive(pr_start)
{
    register cell idx = *sp++;

    if (_is_fiber_stack_full())
        _abort(err_fiber_stack_overflow);

    else if (!_is_valid_fiber_number(idx))
        _abort(err_invalid_fiber_number);

    else if (_is_active_fiber_number(idx))
        _abort(err_active_fiber_not_allowed);

    else {
        _debug("saving fiber %d\n", *fp);
        _print_registers();

        _save_fiber_state();
        *--fp = idx;

        _load_fiber_state();

        _debug("loaded fiber %d\n", *fp);
        _print_registers();
    }
}
__end

__define_primitive("start", pr_start);
