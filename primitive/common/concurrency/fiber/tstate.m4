__primitive(pr_tstate)
{
    register cell idx = *sp;

    if (!_is_valid_task_number(idx))
        _abort(err_invalid_task_number);

    else if (_is_active_task_number(idx))
        _abort(err_active_task_not_allowed);

    else {
        register cell *t = _to_task_ptr(idx);
        *sp = _from_ptr(&t[ta_state]);
    }
}
__end

__define_primitive("tstate", pr_tstate);
