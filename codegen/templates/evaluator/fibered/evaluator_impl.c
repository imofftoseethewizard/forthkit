void
init_evaluator(
    cell *e,
    cell buffer_count,
    cell buffer_size,
    cell evaluator_size,
    cell fiber_count,
    cell fiber_stack_size,
    cell pad_buffer_size,
    cell parameter_stack_size,
    cell return_stack_size,
    cell source_size,
    cell task_count,
    cell word_buffer_size)
{
    e[ea_buffer_count]         = buffer_count;
    e[ea_buffer_size]          = buffer_size;
    e[ea_fiber_count]          = fiber_count;
    e[ea_fiber_stack_size]     = fiber_stack_size;
    e[ea_pad_buffer_size]      = pad_buffer_size;
    e[ea_parameter_stack_size] = parameter_stack_size;
    e[ea_return_stack_size]    = return_stack_size;
    e[ea_size]                 = evaluator_size;
    e[ea_source_size]          = source_size;
    e[ea_task_count]           = task_count;
    e[ea_word_buffer_size]     = word_buffer_size;

    /* signals to evalute() that the evaluator's memory is uninitialized */
    e[ea_top] = 0;

    evaluate(e, "", -1, NULL);
}

int
evaluate(cell *evaluator, const char *source, int storage_fd, cell *primitives)
{
	/*{ evaluator_variables }*/

	/*{ primitive_decls }*/

	static cell internal_primitives[__primitive_count]; // TODO __primitive_count

    if (!evaluator) {

	    /*{ initialize_primitive_registry }*/

        if (primitives)
            memcpy(primitives, &internal_primitives, sizeof(internal_primitives));

        return sizeof(internal_primitives)/sizeof(cell);
    }

    int result = 0;

    register cell *e = evaluator;

    register char *top;
    register cell *tp;    /* current task */
    register cell *fp;    /* current fiber */

    register cell *fp0;
    register cell *rp0;
    register cell *sp0;

    register char *dp;
    register cell *sp;

    register cell *ip;
    register cell *rp;
    register cell *rp_stop;
    register number steps;

#ifdef BOOTSTRAP
    if (!e[ea_top]) {

        top = (char *)e + e[ea_size] - sizeof(cell);
        e[ea_top] = _from_ptr(top);

        /* reserve large blocks in high memory */

        e[ea_buffers]      = _reserve(e[ea_buffer_count] * e[ea_buffer_size]);
        e[ea_buffer_map]   = _reserve(e[ea_buffer_count] * sizeof(cell));
        e[ea_pad]          = _reserve(e[ea_pad_buffer_size]);
        e[ea_source_addr]  = _reserve(e[ea_source_size]);
        e[ea_word_buffer0] = _reserve(e[ea_word_buffer_size]);
        e[ea_word_buffer1] = _reserve(e[ea_word_buffer_size]);
        e[ea_fp0]          = _reserve(e[ea_fiber_count] * sizeof(cell)) + e[ea_fiber_count] * sizeof(cell);
        e[ea_fibers]       = _reserve(_fiber_area);
        e[ea_tasks]        = _reserve(_task_area);

        _debug("tasks:        %x\n", e[ea_tasks]);
        _debug("fibers:       %x\n", e[ea_fibers]);
        _debug("fp0:          %x\n", e[ea_fp0]);
        _debug("word_buffer1: %x\n", e[ea_word_buffer1]);
        _debug("word_buffer0: %x\n", e[ea_word_buffer0]);
        _debug("source_addr:  %x\n", e[ea_source_addr]);
        _debug("buffer_map:   %x\n", e[ea_buffer_map]);
        _debug("buffers:      %x\n", e[ea_buffers]);

        for (register int i = 0; i < e[ea_buffer_count]; i++)
            *(_to_ptr(e[ea_buffer_map]) + i) = -1;

        for (register int i = 0; i < e[ea_fiber_count]; i++) {
            register cell *f = _to_fiber_ptr(i);
            f[fa_ip] = 0;
            f[fa_rp] = f[fa_rp_stop] = f[fa_rp0] = _from_ptr(f) + _fiber_size;
            f[fa_steps] = -1;
            f[fa_task] = 0;
        }

        for (register int i = 0; i < e[ea_task_count]; i++) {
            register cell *t = _to_task_ptr(i);
            t[ta_bottom] = i == 0 ? _from_ptr(e) : 0;
            t[ta_top] = i == 0 ? _from_ptr(top) : 0;
            t[ta_dp] = i == 0 ? _from_ptr(&e[engine_attribute_count]) : 0;
            t[ta_sp] = t[ta_sp0] = _from_ptr(t) + _task_size;
            t[ta_forth] = 0;
            t[ta_context] =
            t[ta_current] = _from_ptr(&t[ta_forth]);
            t[ta_base] = 10;
            t[ta_state] = 0;
            t[ta_interpret] = 0;
        }

        e[ea_fp]           = e[ea_fp0];
        e[ea_source_idx]   = 0;
        e[ea_source_len]   = 0;
        e[ea_blk]          = 0;
        e[ea_next_buffer]  = 0;
        e[ea_scr]          = 0;

        fp0 = fp = _to_ptr(e[ea_fp0]);
        *--fp = _primary_fiber;

        _load_fiber_state();

        _define_constant("ea_size",                 _from_ptr(&e[ea_size]));
        _define_constant("ea_top",                  _from_ptr(&e[ea_top]));
        _define_constant("ea_buffer_size",          _from_ptr(&e[ea_buffer_size]));
        _define_constant("ea_buffer_count",         _from_ptr(&e[ea_buffer_count]));
        _define_constant("ea_fiber_count",          _from_ptr(&e[ea_fiber_count]));
        _define_constant("ea_fiber_stack_size",     _from_ptr(&e[ea_fiber_stack_size]));
        _define_constant("ea_pad_buffer_size",      _from_ptr(&e[ea_pad_buffer_size]));
        _define_constant("ea_parameter_stack_size", _from_ptr(&e[ea_parameter_stack_size]));
        _define_constant("ea_return_stack_size",    _from_ptr(&e[ea_return_stack_size]));
        _define_constant("ea_source_size",          _from_ptr(&e[ea_source_size]));
        _define_constant("ea_task_count",           _from_ptr(&e[ea_task_count]));
        _define_constant("ea_word_buffer_size",     _from_ptr(&e[ea_word_buffer_size]));

        _define_constant("ea_buffer_map",           _from_ptr(&e[ea_buffer_map]));
        _define_constant("ea_buffers",              _from_ptr(&e[ea_buffers]));
        _define_constant("ea_error_msg_addr",       _from_ptr(&e[ea_error_msg_addr]));
        _define_constant("ea_error_msg_len",        _from_ptr(&e[ea_error_msg_len]));
        _define_constant("ea_fibers",               _from_ptr(&e[ea_fibers]));
        _define_constant("ea_fp",                   _from_ptr(&e[ea_fp]));
        _define_constant("ea_fp0",                  _from_ptr(&e[ea_fp0]));
        _define_constant("ea_pad",                  _from_ptr(&e[ea_pad]));
        _define_constant("ea_source_addr",          _from_ptr(&e[ea_source_addr]));
        _define_constant("ea_tasks",                _from_ptr(&e[ea_tasks]));
        _define_constant("ea_word_buffer0",         _from_ptr(&e[ea_word_buffer0]));
        _define_constant("ea_word_buffer1",         _from_ptr(&e[ea_word_buffer1]));

        _define_constant("ea_blk",                  _from_ptr(&e[ea_blk]));
        _define_constant("ea_next_buffer",          _from_ptr(&e[ea_next_buffer]));
        _define_constant("ea_scr",                  _from_ptr(&e[ea_scr]));
        _define_constant("ea_source_idx",           _from_ptr(&e[ea_source_idx]));
        _define_constant("ea_source_len",           _from_ptr(&e[ea_source_len]));

        _define_constant("wa_word_name",  0);
        _define_constant("wa_word_link",  sizeof(cell));
        _define_constant("wa_word_flags", 2*sizeof(cell));
        _define_constant("wa_word_xt",    3*sizeof(cell));

        /*{ primitive_word_definitions }*/
        /*{ compiled_word_definitions }*/

        _save_fiber_state();
    }
#endif

    _debug("interpreting source '%s'\n", source);

    /* copy source into evaluator memory */

    memcpy(_to_ptr(e[ea_source_addr]), source, e[ea_source_len] = strlen(source));
    e[ea_source_idx] = 0;

    /* push new fiber for the interpreter task onto fiber stack */

    fp = fp0 = _to_ptr(e[ea_fp0]);
    *--fp = _primary_fiber;

    _load_fiber_state();

    rp = rp_stop = rp0;
    *--rp = 0;
    ip = _to_ptr(tp[ta_interpret]);

    steps = -1;

    _save_fiber_state();

    /*{ evaluator_core }*/

    _debug("done with run: result: %d\n", result);
    _print_stack();

    return result;
}
