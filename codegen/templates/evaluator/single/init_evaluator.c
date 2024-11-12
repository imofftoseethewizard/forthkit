void
init_evaluator(
    cell *e,
    cell buffer_count,
    cell buffer_size,
    cell evaluator_size,
    cell pad_buffer_size,
    cell parameter_stack_size,
    cell return_stack_size,
    cell source_size,
    cell word_buffer_size)
{
    e[ea_buffer_count]         = buffer_count;
    e[ea_buffer_size]          = buffer_size;
    e[ea_pad_buffer_size]      = pad_buffer_size;
    e[ea_parameter_stack_size] = parameter_stack_size;
    e[ea_return_stack_size]    = return_stack_size;
    e[ea_size]                 = evaluator_size;
    e[ea_source_size]          = source_size;
    e[ea_word_buffer_size]     = word_buffer_size;

    /* signals to evalute() that the evaluator's memory is uninitialized */
    e[ea_top] = 0;

    evaluate(e, "", -1, NULL);
}
