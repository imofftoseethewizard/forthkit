/*|

TODO

  |*/

#define _base()         e[ea_base]
#define _context()      e[ea_context]
#define _current()      e[ea_current]
#define _forth()        e[ea_forth]
#define _interpret()    e[ea_interpret]
#define _state()        e[ea_state]

#define _set_base(x)      e[ea_base]      = (x)
#define _set_context(x)   e[ea_context]   = (x)
#define _set_current(x)   e[ea_current]   = (x)
#define _set_interpret(x) e[ea_interpret] = (x)
#define _set_state(x)     e[ea_state]     = (x)

enum engine_attribute {
    /* attributes set by init_evaluator */

    ea_size, /* from evaluator_size parameter */
    ea_top,  /* == 0 implies that the evaluator's memory has not been set
                up yet */

    ea_ip,
    ea_rp,
    ea_rp0,

    ea_bottom,
    ea_dp,
    ea_sp,
    ea_sp0,
    ea_base,
    ea_context,
    ea_current,
    ea_state,
    ea_interpret,
    ea_forth,

    ea_buffer_size,
    ea_buffer_count,
    ea_pad_buffer_size,
    ea_parameter_stack_size,
    ea_return_stack_size,
    ea_source_size,
    ea_word_buffer_size,

    /* attributes referencing reserved memory areas */
    ea_buffer_map,
    ea_buffers,
    ea_error_msg_addr,
    ea_error_msg_len,
    ea_pad,
    ea_source_addr,
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

#define _save_evaluator_state()                \
do {                                           \
    e[ea_dp]  = _from_ptr(dp);                 \
    e[ea_ip]  = rp == rp0 ? 0 : _from_ptr(ip); \
    e[ea_rp0] = _from_ptr(rp0);                \
    e[ea_rp]  = _from_ptr(rp);                 \
    e[ea_sp0] = _from_ptr(sp0);                \
    e[ea_sp]  = _from_ptr(sp);                 \
    e[ea_top] = _from_ptr(top);                \
                                               \
} while (0)

#define _load_evaluator_state()             \
do {                                        \
                                            \
    dp  = (char *)_to_ptr(e[ea_dp]);        \
    ip  = e[ea_ip] ? _to_ptr(e[ea_ip]) : 0; \
    rp  = _to_ptr(e[ea_rp]);                \
    rp0 = _to_ptr(e[ea_rp0]);               \
    sp  = _to_ptr(e[ea_sp]);                \
    sp0 = _to_ptr(e[ea_sp0]);               \
    top = (char *)_to_ptr(e[ea_top]);       \
                                            \
} while (0)

#if VERBOSE

/*{ define_print_registers }*/

#endif
