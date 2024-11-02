enum engine_attribute {
    /* attributes set by init_evaluator */

    ea_size, /* from evaluator_size parameter */
    ea_top,  /* == 0 implies that the evaluator's memory has not been set
                up yet */

    ea_buffer_size,
    ea_buffer_count,
    ea_fiber_count,
    ea_fiber_stack_size,
    ea_pad_buffer_size,
    ea_parameter_stack_size,
    ea_return_stack_size,
    ea_source_size,
    ea_task_count,
    ea_word_buffer_size,

    /* attributes referencing reserved memory areas */
    ea_buffer_map,
    ea_buffers,
    ea_error_msg_addr,
    ea_error_msg_len,
    ea_fibers,
    ea_fp,
    ea_fp0,
    ea_pad,
    ea_source_addr,
    ea_tasks,
    ea_word_buffer0,
    ea_word_buffer1,

    /* miscellaneous */
    ea_blk,
    ea_next_buffer,
    ea_scr,
    ea_source_idx,
    ea_source_len,

    /* must be last */
    engine_attribute_count
};
