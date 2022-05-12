__primitive(pr_fiber)
{
    register int idx;

    /* start at 1 since 0 is the primary fiber */
    for (idx = 1; idx < FIBER_COUNT; idx++)
        if (_to_fiber_ptr(idx)[fa_ip] == 0)
            break;

    if (idx == FIBER_COUNT)
        _abort(err_no_fibers_available);

    else {
        register cell* f = _to_fiber_ptr(idx);
        f[fa_ip] = *sp;
        f[fa_rp0] = _from_ptr(f + _fiber_size);
        f[fa_rp] = f[fa_rp0] - sizeof(cell);
        *_to_ptr(f[fa_rp]) = 0;
        f[fa_rp_stop] = f[fa_rp0];
        f[fa_steps] = -1;
        f[fa_task] = e[ea_task];
        *sp = idx;
    }
}
__end

__define_primitive("fiber", pr_fiber);
