pr_task:
{
    /* task ( u addr -- t )


     */
    register int idx;

    for (idx = 0; idx < e[ea_task_count]; idx++)
        if (_to_task_ptr(idx)[ta_dp] == 0)
            break;

    if (idx == e[ea_task_count])
        _abort(err_no_tasks_available);

    else {
        register cell* t = _to_task_ptr(idx);
        t[ta_bottom] = *sp++;
        t[ta_top] = t[ta_bottom] + *sp - sizeof(cell);
        t[ta_dp] = t[ta_bottom];
        t[ta_sp] = t[ta_sp0];
        t[ta_base] = tp[ta_base];
        t[ta_forth] = tp[ta_forth];
        t[ta_context] =
        t[ta_current] = _from_ptr(&t[ta_forth]);
        t[ta_state] = 0;
        t[ta_interpret] = tp[ta_interpret];
        *sp = idx;
    }
}
