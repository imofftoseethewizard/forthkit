#if DEBUG

#define _debug_break() (steps == 0)
#define _debug_count_step() do { if (steps > 0) steps -= 1; } while (0)

#define _declare_debug_variables()           \
    register cell *rp_stop;                  \
    register number steps

#define _initialize_debug_variables()        \
    e[ea_rp_stop]     = 0;                   \
    e[ea_steps]       = -1 /* negative numbers indicate no limit */

#define _load_debug_variables()              \
    rp_stop = _to_ptr(e[ea_rp_stop]);        \
    steps = e[ea_steps]

#define _store_debug_variables()             \
    e[ea_rp_stop] = _from_ptr(rp_stop);      \
    e[ea_steps] = steps

#define _debug_load_fiber_state()            \
    rp_stop = _to_ptr(fiber[fa_rp_stop];)    \
    steps = fiber[fa_steps]

#define _debug_save_fiber_state()            \
    fiber[fa_rp_stop] = _from_ptr(rp_stop);  \
    fiber[fa_steps] = steps

#else

#define _debug_break() 0
#define _debug_count_step()
#define _declare_debug_variables()
#define _initialize_debug_variables()
#define _load_debug_variables()
#define _store_debug_variables()
#define _debug_load_fiber_state()
#define _debug_save_fiber_state()

#endif /* DEBUG */
