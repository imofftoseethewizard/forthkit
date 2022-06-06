__primitive(pr_fsteps)
{
    register cell idx = *sp;

    if (!_is_valid_fiber_number(idx))
        _abort(err_invalid_fiber_number);

    else if (_is_active_fiber_number(idx))
        _abort(err_active_fiber_not_allowed);

    else {
        register cell *f = _to_fiber_ptr(idx);
        *sp = _from_ptr(&f[fa_steps]);
    }
}
__end

__define_primitive(`"fsteps"', pr_fsteps);