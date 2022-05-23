__primitive(pr_start)
{
    register cell idx = *sp++;

    if (fp0 - fp == e[ea_fiber_stack_size] * sizeof(cell))
        _abort(err_fiber_stack_overflow);

    else if (idx >= e[ea_fiber_count])
        _abort(err_invalid_fiber_number);

    else {
        _save_fiber_state();
        *--fp = idx;
        _load_fiber_state();
    }
}
__end

__define_primitive("start", pr_start);
