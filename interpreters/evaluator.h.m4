include(`bounds.h')
include(`log.h')
include(`types.h')

`#define' EVALUATOR_FAMILY_NAME "__evaluator_family_name"

#define c_msb ((cell)1 << (sizeof(cell) * 8 - 1))

extern void init_evaluator(
    cell *evaluator,
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
    cell word_buffer_size);

extern int evaluate(cell *evaluator, const char *source, int storage_fd, cell *primitive_registry);
extern cell *create_evaluator_image(cell *e0, cell *e1, int *image_size);
extern cell *load_evaluator_image(const char *image, int image_size);

#define _from_high_word(x) ((x) >> (sizeof(number)*8))
#define _from_low_word(x)  ((number)(x))
#define _to_high_word(x)   (((double_number)(x)) << (sizeof(number)*8))
#define _to_low_word(x)    ((double_number)(x))

/* Used in when saving and loading evaluator images */
enum block_type {
    bt_data,
    bt_primitive_references,
    bt_relocation_table,
};

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

#define c_immediate                  0b00000001
#define c_inline                     0b00000010
#define c_primitive                  0b00000100
#define c_value                      0b00001000
#define c_operand_ip_absolute        0b00010000
#define c_operand_ip_offset          0b00100000
#define c_operand_indirect_ip_offset 0b01000000
#define c_operand_literal            0b10000000

#define _quote(x) #x
#define _from_pr(x) _from_pv(_pr_value(x))

#define _string_len(x)  *(unsigned char *)(x)
#define _string_addr(x) (char *)((unsigned char *)(x) + 1)

#define _compile_pr(x) _store_data(_from_pr(x))
#define _compile_cw(x) _store_data(e[e[ea_size] / sizeof(cell) - x - 1])

#define _set_word_flags(x, flags)       *((cell *)(x) + 2) |= (flags)
#define _clear_word_flags(x, flags)     *((cell *)(x) + 2) &= ~(flags)
#define _get_word_flags(x)              *((cell *)(x) + 2)

#define _get_word_interpretation_ptr(x) ((cell *)(x) + 3)
#define _get_word_interpretation(x)     _from_ptr(_get_word_interpretation_ptr(x))

#define _store_word_name()                                        \
do {                                                              \
    register cell name = _from_ptr(dp);                           \
    register cell *string_addr = _to_ptr(*sp);                    \
    register unsigned char n = *(unsigned char *)string_addr;         \
                                                                  \
    memcpy(dp, string_addr, n + 1);             \
    dp += n + 1;                                \
                                                                  \
    *sp = name;                                                   \
                                                                  \
} while (0)


#define _word_header(flags)                                       \
       /* _word_header: ( n -- addr ) [xp]    */                  \
                                                                  \
       /* Align dp to a cell boundary.      */                    \
       dp = (char *)_align(dp);                                   \
                                                                  \
       /* Save address of new word.           */                  \
       *--rp = _from_ptr(dp);                                     \
                                                                  \
       /* Copy name address to word entry.    */                  \
       _store_data(*sp++);                                        \
                                                                  \
       /* Vocabulary list link.               */                  \
       _store_data(*_to_ptr(tp[ta_current]));                     \
                                                                  \
       /* Add to current vocabulary.          */                  \
       *_to_ptr(tp[ta_current]) = *rp++;                          \
                                                                  \
       /* Word flags.                         */                  \
       _store_data(flags)

#define _next_word(x) *(_to_ptr(x) + 1)

#define _compiled_word_ref(e, l) e[e[ea_size] / sizeof(cell) - l - 1]
#define _register_compiled_word(l) _compiled_word_ref(e, l) = _from_ptr(dp)
#define _compiled_word(s, l, flags)                               \
        _begin_define_word(s, flags);                             \
        _register_compiled_word(l)

#define _begin_define_word(s, flags)                              \
    do {                                                          \
        *--sp = _from_ptr(dp);                                    \
        dp = store_counted_string((s), dp);                       \
        _word_header(flags);                                      \
    } while(0)

#define _define_primitive_ext(s, l, cw_l, flags)                  \
        _info("defining %-16s %lx\n", s, (long)_from_pr(l));      \
        _begin_define_word(s, c_inline | c_primitive | (flags));  \
        _register_compiled_word(cw_l);                            \
        _compile_pr(l);                                           \
        _compile_pr(op_exit);

#define _define_parsing_primitive(s, l, cw_l)                     \
        _info("defining %-16s %lx\n", s, (long)_from_pr(l));      \
        _begin_define_word(s, c_primitive);                       \
        _register_compiled_word(cw_l);                            \
        _compile_literal(32);                                     \
        _compile_literal(_from_ptr(&e[ea_word_buffer1]));         \
        _compile_pr(pr_fetch);                                    \
        _compile_pr(pr_word);                                     \
        _compile_pr(l);                                           \
        _compile_pr(op_exit);

#define _define_primitive(s, l, cw_l)           _define_primitive_ext(s, l, cw_l, 0)
#define _define_immediate_primitive(s, l, cw_l) _define_primitive_ext(s, l, cw_l, c_immediate)

#define _define_constant(s, v)                                    \
        _info("defining constant %-16s %d\n", s, v);              \
        _begin_define_word(s, c_value);                           \
        _compile_literal(v);                                      \
        _compile_pr(op_exit);

#define _primary_fiber 0
#define _primary_task 0

#define _fiber_area (_fiber_size * e[ea_fiber_count])
#define _task_area (_task_size * e[ea_task_count])

#define _to_buffer_ptr(n) ((char *)_to_ptr(e[ea_buffers] + n * e[ea_buffer_size]))
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

#define _enter()                                                  \
do {                                                              \
    *--rp = _from_ptr(ip+1);                                      \
    ip = _to_ptr(*ip);                                            \
    _check_return_stack_bounds();                                 \
} while (0)

include(__preamble)dnl
include(__memory_model)dnl
include(__execution_model)dnl
include(__evaluator_primitives)dnl
include(__compiled_words)dnl

undivert(__header_definitions)dnl

enum compiled_word_labels {
undivert(__compiled_word_declarations)dnl
};

__discard_all_diversions()dnl
