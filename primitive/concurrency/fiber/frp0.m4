__primitive(pr_frp0)
{
    register cell idx = *sp;

    if (_is_valid_fiber_number(idx))
        _abort(err_invalid_fiber_number);

    else {
        register cell *f = _to_fiber_ptr(idx);
        *sp = _from_ptr(&f[fa_rp0]);
    }
}
__end

__define_primitive(`"frp0"', pr_frp0);
