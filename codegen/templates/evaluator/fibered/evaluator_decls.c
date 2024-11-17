/*|

TODO

  |*/

#define _current() tp[ta_current]

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

#define _primary_fiber 0
#define _primary_task 0

enum fiber_attribute {
    fa_ip,
    fa_rp,
    fa_rp0,
    fa_rp_stop,
    fa_steps,
    fa_task,

    /* must be last */
    fiber_attribute_count
};

#define _fiber_size ((fiber_attribute_count + e[ea_return_stack_size]) * sizeof(cell))

enum task_attribute {
    ta_bottom,
    ta_top,
    ta_dp,
    ta_sp,
    ta_sp0,
    ta_base,
    ta_context,
    ta_current,
    ta_state,
    ta_interpret,
    ta_forth,

    /* must be last */
    task_attribute_count
};

#define _task_size ((task_attribute_count + e[ea_parameter_stack_size]) * sizeof(cell))

#define _fiber_area (_fiber_size * e[ea_fiber_count])
#define _task_area (_task_size * e[ea_task_count])

#define _to_fiber_ptr(n) ((cell *)((char *)_to_ptr(e[ea_fibers]) + _fiber_size * (n)))
#define _to_task_ptr(n)  ((cell *)((char *)_to_ptr(e[ea_tasks]) + _task_size * (n)))

#define _save_fiber_state()                                       \
do {                                                              \
    register cell *fiber = _to_fiber_ptr(*fp);                    \
                                                                  \
    fiber[fa_ip]  = rp == rp0 ? 0 : _from_ptr(ip);                \
    fiber[fa_rp]  = _from_ptr(rp);                                \
    fiber[fa_rp0] = _from_ptr(rp0);                               \
    fiber[fa_rp_stop] = _from_ptr(rp_stop);                       \
    fiber[fa_steps] = steps;                                      \
                                                                  \
    tp[ta_dp] = _from_ptr(dp);                                    \
    tp[ta_sp] = _from_ptr(sp);                                    \
    tp[ta_sp0] = _from_ptr(sp0);                                  \
    tp[ta_top] = _from_ptr(top);                                  \
                                                                  \
} while (0)

#define _load_fiber_state()                                       \
do {                                                              \
    register cell *fiber = _to_fiber_ptr(*fp);                    \
                                                                  \
    ip      = fiber[fa_ip] ? _to_ptr(fiber[fa_ip]) : 0;           \
    rp      = _to_ptr(fiber[fa_rp]);                              \
    rp0     = _to_ptr(fiber[fa_rp0]);                             \
    rp_stop = _to_ptr(fiber[fa_rp_stop]);                         \
    steps   = fiber[fa_steps];                                    \
    tp      = _to_task_ptr(fiber[fa_task]);                       \
                                                                  \
    dp = (char *)_to_ptr(tp[ta_dp]);                              \
    sp = _to_ptr(tp[ta_sp]);                                      \
    sp0 = _to_ptr(tp[ta_sp0]);                                    \
    top = (char *)_to_ptr(tp[ta_top]);                            \
                                                                  \
} while (0)

#define _end_fiber()                                              \
do {                                                              \
    _save_fiber_state();                                          \
    fp++;                                                         \
} while (0)

#if VERBOSE

#define _print_fiber_stack()                                             \
do {                                                                     \
    register cell *fpx = fp0;                                            \
                                                                         \
    _debug("fiber stack: ");                                             \
                                                                         \
    while (fp < fpx)                                                     \
        _debug("%d ", (int)*--fpx);                                      \
                                                                         \
    _debug("\n");                                                        \
} while(0)

#define _print_registers()                                               \
do {                                                                     \
    _debug("s: %8lx, ip: %8lx; *ip: %8lx, *(ip+1): %8lx, rp: %8lx, *rp: %8lx, sp: %8lx, *sp: %8lx, dp: %8lx src: %.*s\n",  \
           steps, \
           _from_ptr(ip), ip?*ip:0, ip?*(ip+1):0,        \
           _from_ptr(rp), rp?*rp:0,                      \
           _from_ptr(sp), sp?*sp:0,                      \
           (long)_from_ptr(dp),                          \
           e[ea_source_len]-e[ea_source_idx], \
           (char *)_to_ptr(e[ea_source_addr]) + e[ea_source_idx]);      \
} while (0)

#else

#define _print_fiber_stack()

#endif
#ifdef BOUNDS_CHECKING

#define _check_fiber_stack_bounds()                  \
do {                                                 \
    if (fp < fp0 - e[ea_fiber_stack_size])           \
        _abort(err_fiber_stack_overflow);            \
    else if (fp > fp0)                               \
        _abort(err_fiber_stack_underflow);           \
} while (0)

#define _check_task_address(t)
#define _check_task_memory()
#define _check_thread_memory()

#define _is_active_fiber_number(x) ((x) == *fp)
#define _is_fiber_stack_full() (fp0 - fp == e[ea_fiber_stack_size])
#define _is_valid_fiber_number(x) ((cell)(x) < e[ea_fiber_count])

#define _is_active_task_number(x) ((x) == _to_fiber_ptr(*fp)[fa_task])
#define _is_primary_task_number(x) ((x) == _primary_task)
#define _is_valid_task_number(x) ((cell)(x) < e[ea_task_count])

#else

#define _check_fiber_stack_bounds()
#define _check_task_address()
#define _check_task_memory()
#define _check_thread_memory()

#define _is_active_fiber_number() 0
#define _is_fiber_stack_full() 0
#define _is_valid_fiber_number() 1

#define _is_active_task_number(x) 0
#define _is_primary_task_number(x) 0
#define _is_valid_task_number(x) 1

#endif
