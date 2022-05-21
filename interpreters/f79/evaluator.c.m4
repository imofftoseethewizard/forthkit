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

    e[ea_forth] = 0;
    e[ea_top]   = _from_ptr((char *)e + evaluator_size - sizeof(cell));
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

    /* fiber stack */
    cell *fp;
    cell *fp0;

    /* Contains the throw code for uncaught exceptions. */
    int result = 0;

    char *dp;
    cell *rp0;
    cell *sp0;

    if (!e[ea_interpret]) {

        /* reserve large blocks in high memory */

        e[ea_buffers]      = _reserve(e[ea_buffer_count] * e[ea_buffer_size]);
        e[ea_buffer_map]      = _reserve(e[ea_buffer_count] * sizeof(cell));
        e[ea_number_pad]   = _reserve(_c_number_pad_size);
        e[ea_source_addr]  = _reserve(e[ea_source_size]);
        e[ea_word_buffer0] = _reserve(e[ea_word_buffer_size]);
        e[ea_word_buffer1] = _reserve(e[ea_word_buffer_size]);
        e[ea_fp0]          = _reserve(e[ea_fiber_count] * sizeof(cell)) + e[ea_fiber_count];
        e[ea_fibers]       = _reserve(_fiber_area);
        e[ea_tasks]        = _reserve(_task_area);

        for (register int i = 0; i < e[ea_buffer_count]; i++)
            *(_to_ptr(e[ea_buffer_map]) + i) = -1;

        for (register int i = 0; i < e[ea_fiber_count]; i++) {
            register cell *f = _to_ptr(e[ea_fibers]) + i * _fiber_size;
            f[fa_ip] = 0;
            f[fa_rp] = f[fa_rp_stop] = f[fa_rp0] = _from_ptr(f) + _fiber_size;
            f[fa_steps] = -1;
            f[fa_task] = e[ea_tasks];
        }

        for (register int i = 0; i < e[ea_task_count]; i++) {
            register cell *t = _to_ptr(e[ea_tasks]) + i * _task_size;
            t[ta_dp] = _from_ptr(&e[ea_end_tasks]);
            t[ta_sp] = t[ta_sp0] = _from_ptr(t) + _task_size;
            t[ta_context] = 0;
            t[ta_current] = _from_ptr(&t[ta_forth]);
            t[ta_base] = 10;
            t[ta_state] = 0;
            t[ta_interpret] = 0;
        }

        e[ea_task] = 0;
        tp = _to_task_ptr(e[ea_task]);

        fp0 = fp = _to_ptr(e[ea_fp0]);
        rp0 = rp = &e[ea_primary_fiber + fiber_attribute_count + RETURN_STACK_SIZE];
        sp0 = sp = &e[ea_primary_task + task_attribute_count + PARAMETER_STACK_SIZE];
        dp = (char *)&e[ea_end_tasks];
        steps = -1; /* negative numbers indicate no limit */

        /* registers */
        fp[fa_ip]          = 0;

        e[ea_rp]           = _from_ptr(rp);
        e[ea_sp]           = _from_ptr(sp);
        e[ea_dp]           = _from_ptr(dp);
        e[ea_rp_stop]      = 0;
        e[ea_steps]        = steps;

        /* internal state */
        e[ea_base]         = 10;
        e[ea_context]      = 0;
        e[ea_current]      = _from_ptr(&e[ea_forth]);
        e[ea_forth]        = 0;
        e[ea_fp]           = e[ea_fp0];
        e[ea_rp0]          = e[ea_rp];
        e[ea_source_idx]   = 0;
        e[ea_source_len]   = 0;
        e[ea_sp0]          = e[ea_sp];
        e[ea_state]        = 0;
        e[ea_blk]          = 0;

        e[ea_next_buffer]  = 0;
        e[ea_scr]          = 0;

        /*_check_thread_memory();*/

        undivert(__primitive_word_definitions)
        undivert(__compiled_word_definitions)dnl
        e[ea_context] = _from_ptr(&e[ea_forth]);
        _check_dictionary_bounds();
        e[ea_dp] = _from_ptr(dp);
    }

    /*_check_fiber_stack_bounds();
    _check_task_memory();*/

    /* The first run will have context == 0. The preamble detects that and
       defines primitives and the bootstrap interpreter.
     */
    if (source) {

        sp  = _to_ptr(e[ea_sp]);
        rp  = _to_ptr(e[ea_rp]);
        tp  = _to_task_ptr(e[ea_task]);

        dp = (char *)_to_ptr(e[ea_dp]);
        fp0 = _to_ptr(e[ea_fp0]);
        rp0 = _to_ptr(e[ea_rp0]);
        sp0  = _to_ptr(e[ea_sp0]);

        _debug("interpreting source '%s'\n", source);

        memcpy(_to_ptr(e[ea_source_addr]), source, e[ea_source_len] = strlen(source));
        e[ea_source_idx] = 0;

        /* push new fiber for the interpreter task onto fiber stack */

        fp = fp0;
        *--fp = _primary_fiber;

        rp = rp0;
        *--rp = 0;
        ip = _to_ptr(e[ea_interpret]);

        steps = -1;

        _save_fiber_state();

    } else {

        fp  = _to_ptr(e[ea_fp]);
        fp0 = _to_ptr(e[ea_fp0]);
        ip  = _to_ptr(fp[fa_ip]);
        sp  = _to_ptr(e[ea_sp]);
        rp  = _to_ptr(e[ea_rp]);
        tp  = _to_task_ptr(e[ea_task]);

        dp = (char *)_to_ptr(e[ea_dp]);
        rp0 = _to_ptr(e[ea_rp0]);
        sp0  = _to_ptr(e[ea_sp0]);
    }

    __implement_evaluator_core() dnl

    /* Store state back in the evaluator structure. */
    /* _save_task_state(); */
    e[ea_sp] = _from_ptr(sp);
    e[ea_dp] = _from_ptr(dp);

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
