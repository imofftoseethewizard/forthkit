__primitive(pr_end)
{
    _save_fiber_state();

    fp++;

    if (fp0 == fp)
        ip = 0;
    else
        _load_fiber_state();
}
__end

__define_primitive("end", pr_end);