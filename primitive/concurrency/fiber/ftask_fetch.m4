__primitive(pr_ftask_fetch)
{
    register cell idx = *sp;

    if (!_is_valid_fiber_number(idx))
        _abort(err_invalid_fiber_number);

    else {
        register cell *f = _to_fiber_ptr(idx);
        *sp = f[fa_task];
    }

}
__end

__define_primitive("ftask@", pr_ftask_fetch);
