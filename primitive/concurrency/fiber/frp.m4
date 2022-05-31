__primitive(pr_frp)
{
    register cell idx = *sp;

    if (_is_valid_fiber_number(idx))
        _abort(err_invalid_fiber_number);

    else {
        register cell *f = _to_fiber_ptr(idx);
        *sp = _from_ptr(&f[fa_rp]);
    }
}
__end

__define_primitive(`"frp"', pr_frp);
