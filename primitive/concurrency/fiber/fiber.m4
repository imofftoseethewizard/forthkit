__primitive(pr_fiber)
{
    register int idx;

    for (idx = 0; idx < e[ea_fiber_count]; idx++)
        if (_to_fiber_ptr(idx)[fa_ip] == 0)
            break;

    if (idx == e[ea_fiber_count])
        _abort(err_no_fibers_available);

    else {
        register cell* f = _to_fiber_ptr(idx);
        f[fa_ip] = *sp;
        f[fa_rp0] = _from_ptr(f + _fiber_size);
        f[fa_rp] = f[fa_rp0] - sizeof(cell);
        *_to_ptr(f[fa_rp]) = 0;
        f[fa_rp_stop] = f[fa_rp0];
        f[fa_steps] = -1;
        f[fa_task] = f[fa_task];
        *sp = idx;
    }
}
__end

__define_primitive("fiber", pr_fiber);
