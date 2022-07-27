    static primitive_descriptor primitive_descs[] = {
        stack_foreach(`__primitive_descs', `__show')};

    __define_constant("size",                 sizeof(cell) * ea_size)
    __define_constant("top",                  sizeof(cell) * ea_top)
    __define_constant("buffer_size",          sizeof(cell) * ea_buffer_size)
    __define_constant("buffer_count",         sizeof(cell) * ea_buffer_count)
    __define_constant("fiber_count",          sizeof(cell) * ea_fiber_count)
    __define_constant("fiber_stack_size",     sizeof(cell) * ea_fiber_stack_size)
    __define_constant("pad_buffer_size",      sizeof(cell) * ea_pad_buffer_size)
    __define_constant("parameter_stack_size", sizeof(cell) * ea_parameter_stack_size)
    __define_constant("return_stack_size",    sizeof(cell) * ea_return_stack_size)
    __define_constant("source_size",          sizeof(cell) * ea_source_size)
    __define_constant("task_count",           sizeof(cell) * ea_task_count)
    __define_constant("word_buffer_size",     sizeof(cell) * ea_word_buffer_size)

    __define_constant("buffer_map",           sizeof(cell) * ea_buffer_map)
    __define_constant("buffers",              sizeof(cell) * ea_buffers)
    __define_constant("error_msg_addr",       sizeof(cell) * ea_error_msg_addr)
    __define_constant("error_msg_len",        sizeof(cell) * ea_error_msg_len)
    __define_constant("fibers",               sizeof(cell) * ea_fibers)
    __define_constant("fp",                   sizeof(cell) * ea_fp)
    __define_constant("fp0",                  sizeof(cell) * ea_fp0)
    __define_constant("pad",                  sizeof(cell) * ea_pad)
    __define_constant("source_addr",          sizeof(cell) * ea_source_addr)
    __define_constant("tasks",                sizeof(cell) * ea_tasks)
    __define_constant("word_buffer0",         sizeof(cell) * ea_word_buffer0)
    __define_constant("word_buffer1",         sizeof(cell) * ea_word_buffer1)

    __define_constant("blk",                  sizeof(cell) * ea_blk)
    __define_constant("next_buffer",          sizeof(cell) * ea_next_buffer)
    __define_constant("scr",                  sizeof(cell) * ea_scr)
    __define_constant("source_idx",           sizeof(cell) * ea_source_idx)
    __define_constant("source_len",           sizeof(cell) * ea_source_len)

    __define_constant("state",                sizeof(cell) * ea_state)

    __define_constant("system-reserved", sizeof(cell) * (evaluator_attribute_count+4))

    static constant_descriptor constant_descs[] = {
        stack_foreach(`__constant_descs', `__show')};

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
            if (i == 0) {
                t[ta_bottom] =
                  t[ta_dp] = _from_ptr(e);
                t[ta_top] = _from_ptr(top);

                /* reserved for use by pr_interpret */
                e[evaluator_attribute_count] = 0;

                e[evaluator_attribute_count+1] = _from_pv(pr_interpret);
                e[evaluator_attribute_count+2] = _from_pv(op_exit);

                e[ea_interpret] =
                e[ea_pr_interpret] = _from_ptr(&e[evaluator_attribute_count+1]);

                e[ea_state] = 0;
            } else {
                t[ta_bottom] = 0;
                t[ta_top] = 0;
                t[ta_dp] = 0;
            }
            t[ta_sp] = t[ta_sp0] = _from_ptr(t) + _task_size;
            t[ta_forth] = 0;
            t[ta_context] =
              t[ta_current] = _from_ptr(&t[ta_forth]);
            t[ta_latest_xt] = 0;
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

        /*_check_thread_memory();*/

/* #        undivert(__primitive_word_definitions) */
/* #        undivert(__compiled_word_definitions)dnl */

        _save_fiber_state();
    }
