
        top = (char *)e + e[ea_size] - sizeof(cell);
        e[ea_top] = _from_ptr(top);

        /* reserve large blocks in high memory */

        e[ea_buffers]      = _reserve(e[ea_buffer_count] * e[ea_buffer_size]);
        e[ea_buffer_map]   = _reserve(e[ea_buffer_count] * sizeof(cell));
        e[ea_pad]          = _reserve(e[ea_pad_buffer_size]);
        e[ea_source_addr]  = _reserve(e[ea_source_size]);
        e[ea_word_buffer0] = _reserve(e[ea_word_buffer_size]);
        e[ea_word_buffer1] = _reserve(e[ea_word_buffer_size]);

        e[ea_sp] = e[ea_sp0] = _reserve_stack(e[ea_parameter_stack_size] * sizeof(cell));
        e[ea_rp] = e[ea_rp0] = _reserve_stack(e[ea_return_stack_size] * sizeof(cell));

        _debug("word_buffer1: %x\n", e[ea_word_buffer1]);
        _debug("word_buffer0: %x\n", e[ea_word_buffer0]);
        _debug("source_addr:  %x\n", e[ea_source_addr]);
        _debug("buffer_map:   %x\n", e[ea_buffer_map]);
        _debug("buffers:      %x\n", e[ea_buffers]);

        for (register int i = 0; i < e[ea_buffer_count]; i++)
            *(_to_ptr(e[ea_buffer_map]) + i) = -1;

		e[ea_ip] = 0;

		e[ea_bottom]      = _from_ptr(e);
		e[ea_top]         = _from_ptr(top);
		e[ea_dp]          = _from_ptr(&e[engine_attribute_count]);
		e[ea_forth]       = 0;
		e[ea_context]     = _from_ptr(&e[ea_forth]);
		e[ea_current]     = _from_ptr(&e[ea_forth]);
		e[ea_base]        = 10;
		e[ea_state]       = 0;
		e[ea_interpret]   = 0;

        e[ea_source_idx]  = 0;
        e[ea_source_len]  = 0;
        e[ea_blk]         = 0;
        e[ea_next_buffer] = 0;
        e[ea_scr]         = 0;

        _load_evaluator_state();

        _define_constant("ea_size",                 _from_ptr(&e[ea_size]));
        _define_constant("ea_top",                  _from_ptr(&e[ea_top]));
        _define_constant("ea_buffer_size",          _from_ptr(&e[ea_buffer_size]));
        _define_constant("ea_buffer_count",         _from_ptr(&e[ea_buffer_count]));
        _define_constant("ea_pad_buffer_size",      _from_ptr(&e[ea_pad_buffer_size]));
        _define_constant("ea_parameter_stack_size", _from_ptr(&e[ea_parameter_stack_size]));
        _define_constant("ea_return_stack_size",    _from_ptr(&e[ea_return_stack_size]));
        _define_constant("ea_source_size",          _from_ptr(&e[ea_source_size]));
        _define_constant("ea_word_buffer_size",     _from_ptr(&e[ea_word_buffer_size]));

        _define_constant("ea_buffer_map",           _from_ptr(&e[ea_buffer_map]));
        _define_constant("ea_buffers",              _from_ptr(&e[ea_buffers]));
        _define_constant("ea_error_msg_addr",       _from_ptr(&e[ea_error_msg_addr]));
        _define_constant("ea_error_msg_len",        _from_ptr(&e[ea_error_msg_len]));
        _define_constant("ea_pad",                  _from_ptr(&e[ea_pad]));
        _define_constant("ea_source_addr",          _from_ptr(&e[ea_source_addr]));
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
