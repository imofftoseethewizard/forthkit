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
