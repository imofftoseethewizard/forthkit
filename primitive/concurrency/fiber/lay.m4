__primitive(pr_lay)
{
    register cell idx = *sp++;

    if (_is_fiber_stack_full())
        _abort(err_fiber_stack_overflow);

    else if (_is_valid_fiber_number(idx))
        _abort(err_invalid_fiber_number);

    else {
        register cell f = *fp;
        *fp = idx;
        *--fp = f;
    }
}
__end

__define_primitive("lay", pr_lay);
