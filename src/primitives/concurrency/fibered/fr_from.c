pr_fr_from:
{
    register cell idx = *sp;

    if (!_is_valid_fiber_number(idx))
        _abort(err_invalid_fiber_number);

    else if (_is_active_fiber_number(idx))
        _abort(err_active_fiber_not_allowed);

    else {
        register cell *f = _to_fiber_ptr(idx);
        *sp = *_to_ptr(f[fa_rp]);
        f[fa_rp] += sizeof(cell);
    }
}
