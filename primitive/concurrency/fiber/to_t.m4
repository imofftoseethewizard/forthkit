__primitive(pr_to_t)
{
    register cell idx = *sp++;
    fprintf(stderr, "to_t: idx: %d, fp[fa_task]: %lx\n", idx, _to_fiber_ptr(*fp)[fa_task]);

    if (!_is_valid_task_number(idx))
        _abort(err_invalid_task_number);

    else if (_is_active_task_number(idx))
        _abort(err_active_task_not_allowed);

    else {
        register cell *t = _to_task_ptr(idx);
        t[ta_sp] -= sizeof(cell);
        *_to_ptr(t[ta_sp]) = *sp++;
    }
}
__end

__define_primitive(">t", pr_to_t);