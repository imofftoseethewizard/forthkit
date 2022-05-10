#include "config.h"

#include "bounds.h"
#include "debug.h"
#include "errors.h"
#include "log.h"

typedef unsigned CELL_TYPE cell;
typedef CELL_TYPE number;

#define c_msb ((cell)1 << (sizeof(cell) * 8 - 1))

typedef LENGTH_TYPE length_type;

typedef DOUBLE_TYPE double_number;
typedef unsigned DOUBLE_TYPE double_cell;

#define _from_high_word(x) ((x) >> (sizeof(number)*8))
#define _from_low_word(x)  ((number)(x))
#define _to_high_word(x)   (((double_number)(x)) << (sizeof(number)*8))
#define _to_low_word(x)    ((double_number)(x))

enum fiber_attribute {
    fa_ip,
    fa_rp,
    fa_rp0,
    fa_rp_stop,
    fa_steps,
    fa_tp,

    /* must be last */
    fiber_attribute_count
};

enum task_attribute {
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

enum engine_attribute {
    /* attributes common to all tasks */
    ea_size,
    ea_source_addr,
    ea_source_idx,
    ea_source_len,
    ea_blk,
    ea_buffers,
    ea_next_buffer,
    ea_scr,
    ea_fp,
    ea_fp0,

    ea_fiber_stack = ea_fp0,
    ea_end_fiber_stack = ea_fiber_stack + FIBER_COUNT,

    ea_buffer_map = ea_end_fiber_stack,
    ea_end_buffer_map = ea_buffer_map + BUFFER_COUNT,

    ea_source_buffer = ea_end_buffer_map,
    ea_end_source_buffer = ea_source_buffer + SOURCE_SIZE / sizeof(cell),

    /* attributes of the primary fiber */
    ea_primary_fiber = ea_end_source_buffer,

    ea_ip      = ea_primary_fiber + fa_ip,
    ea_rp      = ea_primary_fiber + fa_rp,
    ea_rp0     = ea_primary_fiber + fa_rp0,
    ea_tp      = ea_primary_fiber + fa_tp,
    ea_rp_stop = ea_primary_fiber + fa_rp_stop,
    ea_steps   = ea_primary_fiber + fa_steps,

    ea_end_fibers = ea_primary_fiber + (fiber_attribute_count + RETURN_STACK_SIZE) * FIBER_COUNT,

    /* attributes of the primary task */
    ea_primary_task = ea_end_fibers,

    ea_dp        = ea_primary_task + ta_dp,
    ea_sp        = ea_primary_task + ta_sp,
    ea_sp0       = ea_primary_task + ta_sp0,
    ea_base      = ea_primary_task + ta_base,
    ea_context   = ea_primary_task + ta_context,
    ea_current   = ea_primary_task + ta_current,
    ea_state     = ea_primary_task + ta_state,
    ea_interpret = ea_primary_task + ta_interpret,
    ea_forth     = ea_primary_task + ta_forth,

    ea_end_tasks = ea_primary_task + (task_attribute_count + PARAMETER_STACK_SIZE) * TASK_COUNT,

    /* must be last */
    engine_attribute_count
};

#define c_immediate 0b0001
#define c_inline    0b0010
#define c_primitive 0b0100
#define c_value     0b1000

#define _quote(x) #x
#define _from_pr(x) _from_pv(_pr_value(x))

#define _string_len(x)  *(length_type *)(x)
#define _string_addr(x) (char *)((length_type *)(x) + 1)

#define _compile_pr(x) _store_data(_from_pr(x))
#define _compile_cw(x) _store_data(e[ea_size - x - 1])

#define _set_word_flags(x, flags)       *((cell *)(x) + 2) |= (flags)
#define _clear_word_flags(x, flags)     *((cell *)(x) + 2) &= ~(flags)
#define _get_word_flags(x, flags)       *((cell *)(x) + 2) & ~(flags)

#define _get_word_interpretation_ptr(x) ((cell *)(x) + 3)
#define _get_word_interpretation(x)     _from_ptr(_get_word_interpretation_ptr(x))

#define _store_word_name()                                        \
do {                                                              \
    register cell name = _from_ptr(dp);                           \
    register cell *string_addr = _to_ptr(*sp);                    \
    register length_type n = *(length_type *)string_addr;         \
                                                                  \
    memcpy(dp, string_addr, n + sizeof(length_type));             \
    dp += n + sizeof(length_type);                                \
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
       _store_data(*_to_ptr(e[ea_current]));                      \
                                                                  \
       /* Add to current vocabulary.          */                  \
       *_to_ptr(e[ea_current]) = *rp++;                           \
                                                                  \
       /* Word flags.                         */                  \
       _store_data(flags)

#define _next_word(x) *(_to_ptr(x) + 1)

#define _compiled_word_ref(e, l) e[e[ea_size] / sizeof(cell) - l - 1]
#define _register_compiled_word(l) _compiled_word_ref(e, l) = _from_ptr(dp);
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
        _compile_literal(MAX_WORD_LENGTH);                        \
        _compile_pr(pr_allot);                                    \
        _compile_literal(32);                                     \
        _compile_pr(pr_word);                                     \
        _compile_literal(-MAX_WORD_LENGTH);                       \
        _compile_pr(pr_allot);                                    \
        _compile_pr(l);                                           \
        _compile_pr(op_exit);

#define _define_primitive(s, l, cw_l)           _define_primitive_ext(s, l, cw_l, 0)
#define _define_immediate_primitive(s, l, cw_l) _define_primitive_ext(s, l, cw_l, c_immediate)

#define _save_fiber_state()                                       \
do {                                                              \
    register cell *fiber = _to_ptr(*fp);                          \
    fiber[fa_ip]  = _from_ptr(ip);                                \
    fiber[fa_rp]  = _from_ptr(rp);                                \
    fiber[fa_rp0] = _from_ptr(rp0);                               \
    _debug_save_fiber_state();                                    \
} while (0)

#define _load_fiber_state()                                       \
do {                                                              \
    register cell *fiber = _to_ptr(*fp);                          \
    ip  = _to_ptr(fiber[fa_ip]);                                  \
    rp  = _to_ptr(fiber[fa_rp]);                                  \
    rp0 = _to_ptr(fiber[fa_rp0]);                                 \
    _debug_load_fiber_state();                                    \
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
