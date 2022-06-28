    if (!e[ea_top]) {

        top = (char *)e + e[ea_size] - sizeof(cell);
        e[ea_top] = _from_ptr(top);

        /* reserve large blocks in high memory */

        e[ea_buffers]      = _reserve(e[ea_buffer_count] * e[ea_buffer_size]);
        e[ea_buffer_map]   = _reserve(e[ea_buffer_count] * sizeof(cell));
        e[ea_number_pad]   = _reserve(_c_number_pad_size);
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
        _debug("number_pad:   %x\n", e[ea_number_pad]);
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
            t[ta_bottom] = 0;
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

        /*_check_thread_memory();*/

        undivert(__primitive_word_definitions)
        undivert(__compiled_word_definitions)dnl

        _save_fiber_state();
    }
