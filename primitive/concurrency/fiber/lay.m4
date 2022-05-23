__primitive(pr_lay)
{
    register cell idx = *sp++;

    if (fp0 - fp == e[ea_fiber_stack_size] * sizeof(cell))
        _abort(err_fiber_stack_overflow);

    else if (idx >= e[ea_fiber_count])
        _abort(err_invalid_fiber_number);

    else {
        register cell f = *fp;
        *fp = idx;
        *--fp = f;
    }
}
__end

__define_primitive("lay", pr_lay);
