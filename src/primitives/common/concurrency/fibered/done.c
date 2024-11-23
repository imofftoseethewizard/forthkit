pr_done:
{
    register cell idx = *sp++;

    if (!_is_valid_task_number(idx))
        _abort(err_invalid_task_number);

    else if (_is_primary_task_number(idx))
        _abort(err_primary_task_not_allowed);

    else if (_is_active_task_number(idx))
        _abort(err_active_task_not_allowed);

    else {
        register cell *t = _to_task_ptr(idx);
        t[ta_top] = t[ta_dp] = 0;

        for (register int i = 0; i < e[ea_fiber_count]; i++) {
            register cell *f = _to_fiber_ptr(i);
            if (f[fa_task] == idx) {
                f[fa_ip] = 0;
                f[fa_rp] = f[fa_rp_stop] = f[fa_rp0];
                f[fa_steps] = -1;
                f[fa_task] = 0;
            }
        }
    }
}
