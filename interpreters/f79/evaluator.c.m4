include(__preamble)dnl
include(__execution_model)dnl
include(__evaluator_primitives)dnl
include(__compiled_words)dnl

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>

#include "evaluator.h"

char *store_counted_string(const char *s, char *dp);

void
init_evaluator(
    cell *e,
    cell buffer_count,
    cell buffer_size,
    cell evaluator_size,
    cell fiber_count,
    cell fiber_stack_size,
    cell parameter_stack_size,
    cell return_stack_size,
    cell source_size,
    cell task_count,
    cell word_buffer_size)
{
    e[ea_buffer_count]         = buffer_count;
    e[ea_buffer_size]          = buffer_size;
    e[ea_fiber_count]          = fiber_count;
    e[ea_fiber_stack_size]     = fiber_stack_size;
    e[ea_parameter_stack_size] = parameter_stack_size;
    e[ea_return_stack_size]    = return_stack_size;
    e[ea_size]                 = evaluator_size;
    e[ea_source_size]          = source_size;
    e[ea_task_count]           = task_count;
    e[ea_word_buffer_size]     = word_buffer_size;

    /* signals to evalute() that the evaluator's memory is uninitialized */
    e[ea_top] = 0;
}

int
evaluate(cell *evaluator, const char *source, int storage_fd)
{
    __declare_primitives()dnl

    /* These are the most commonly referenced variables, generally every
       iteration of the interpreter loop. */

    register cell *e = evaluator;
    register cell *ip;
    register cell *rp;
    register cell *sp;
    register cell *tp;
    register cell *rp_stop;
    register number steps;

    /* These are useful to have, but probably not worth putting in a register.
     */

    char *dp;
    cell *fp;
    cell *fp0;
    cell *rp0;
    cell *sp0;

    /* Contains the throw code for uncaught exceptions. */
    int result = 0;

    if (!e[ea_top]) {

        e[ea_top] = _from_ptr((char *)e + e[ea_size] - sizeof(cell));

        /* reserve large blocks in high memory */

        e[ea_buffers]      = _reserve(e[ea_buffer_count] * e[ea_buffer_size]);
        e[ea_buffer_map]   = _reserve(e[ea_buffer_count] * sizeof(cell));
        e[ea_number_pad]   = _reserve(_c_number_pad_size);
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
            t[ta_dp] = _from_ptr(&e[engine_attribute_count]);
            t[ta_sp] = t[ta_sp0] = _from_ptr(t) + _task_size;
            t[ta_context] = 0;
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

        tp[ta_context] = _from_ptr(&tp[ta_forth]);

        _save_fiber_state();
    }

    /*_check_fiber_stack_bounds();
    _check_task_memory();*/

    if (source) {

        _debug("interpreting source '%s'\n", source);

        memcpy(_to_ptr(e[ea_source_addr]), source, e[ea_source_len] = strlen(source));
        e[ea_source_idx] = 0;

        /* push new fiber for the interpreter task onto fiber stack */

        fp = fp0 = _to_ptr(e[ea_fp0]);
        *--fp = _primary_fiber;

        _load_fiber_state();

        rp = rp_stop = rp0;
        *--rp = 0;
        ip = _to_ptr(tp[ta_interpret]);

        steps = -1;

        _save_fiber_state();

    } else {

        fp  = _to_ptr(e[ea_fp]);
        fp0 = _to_ptr(e[ea_fp0]);

        _load_fiber_state();
    }

    __implement_evaluator_core() dnl

    /* Store state back in the evaluator structure. */

    e[ea_fp] = _from_ptr(fp);

    _debug("done with run: result: %d\n", result);
    _print_stack();

    return result;
}

char *
store_counted_string(const char *s, char *dp)
{
    cell n = strlen(s);

    dp = (char *)_align(dp);

    *(length_type *)dp = n;

    strncpy((char *)((length_type *)dp + 1), s, n);

    return dp + sizeof(cell) + n + 1;
}

__discard_all_diversions()dnl
